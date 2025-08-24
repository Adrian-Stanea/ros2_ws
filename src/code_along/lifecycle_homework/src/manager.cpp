#include "lifecycle_homework/manager.hpp"

#include <chrono>

using namespace std::chrono_literals;

namespace lifecycle_homework
{

using ChangeStateClient = rclcpp::Client<lifecycle_msgs::srv::ChangeState>;

Manager::Manager(const rclcpp::NodeOptions & options)
: Node("manager", options)
{
  managed_nodes_ = declare_parameter(
    "managed_nodes", std::vector<std::string>{"managed_node"}
  );

  // Each managed node needs a client to trigger it's state changes
  for (const auto & managed_node:managed_nodes_) {
    change_state_clients_[managed_node] =
      this->create_client<lifecycle_msgs::srv::ChangeState>(managed_node + "/change_state");
  }

  // The code will call a service from a service callback, so we need a callback group to avoid deadlocks + multithreading
  cb_trigger_ = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);

  trigger_srv_ = this->create_service<std_srvs::srv::Trigger>(
    "trigger",
    std::bind(&Manager::activateCallback, this, std::placeholders::_1, std::placeholders::_2),
    rmw_qos_profile_services_default,
    cb_trigger_
  );
}

void Manager::activateCallback(
  const std::shared_ptr<std_srvs::srv::Trigger::Request> request,
  std::shared_ptr<std_srvs::srv::Trigger::Response> response)
{
  response->success = false;

  for (const auto & managed_node: managed_nodes_) {
    while (!change_state_clients_[managed_node]->wait_for_service(1s) && rclcpp::ok()) {
      RCLCPP_INFO(this->get_logger(), "Waiting for %s to be available...", managed_node.c_str());
    }
  }

  auto waitTransition = [this](auto & result, const std::string & node_name) {
      while (result.wait_for(1s) != std::future_status::ready && rclcpp::ok()) {
        RCLCPP_INFO(get_logger(), "Waiting for transition of %s.", node_name.c_str());
      }
    };

  auto config_request = std::make_shared<lifecycle_msgs::srv::ChangeState::Request>();

  // Configure all the managed nodes
  config_request->transition.id = lifecycle_msgs::msg::Transition::TRANSITION_CONFIGURE;
  for (const auto & managed_node: managed_nodes_) {
    auto result = change_state_clients_[managed_node]->async_send_request(config_request);
    waitTransition(result, managed_node);
    if(!result.get()->success) {
      RCLCPP_ERROR(get_logger(), "Failed to configure %s", managed_node.c_str());
      return;
    }
  }

  // Activate all the managed nodes
  config_request->transition.id = lifecycle_msgs::msg::Transition::TRANSITION_ACTIVATE;
  for (const auto & managed_node: managed_nodes_) {
    auto result = change_state_clients_[managed_node]->async_send_request(config_request);
    waitTransition(result, managed_node);
    if(!result.get()->success) {
      RCLCPP_ERROR(get_logger(), "Failed to activate %s", managed_node.c_str());
      return;
    }
  }

  response->success = true;
  RCLCPP_INFO(get_logger(), "All managed nodes activated!");
};

} // namespace lifecycle_homework

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(lifecycle_homework::Manager)