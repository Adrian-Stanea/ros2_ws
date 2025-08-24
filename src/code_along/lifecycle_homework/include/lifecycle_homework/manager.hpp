#ifndef LIFECYCLE_HOMEWORK__MANAGED_NODE_HPP_
#define LIFECYCLE_HOMEWORK__MANAGED_NODE_HPP_

#include "lifecycle_msgs/srv/change_state.hpp"
#include "lifecycle_msgs/srv/get_state.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/trigger.hpp"

#include <vector>
#include <string>
#include <map>

namespace lifecycle_homework
{

using ChangeStateClient = rclcpp::Client<lifecycle_msgs::srv::ChangeState>;

/**
 * @brief Initializes a set of nodes through a service interface
 */
class Manager : public rclcpp::Node
{
public:
  explicit Manager(const rclcpp::NodeOptions & options);

protected:
  // Service to trigger the activation of the managed node
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr trigger_activation_srv_;
  void activateCallback(
    const std::shared_ptr<std_srvs::srv::Trigger::Request> request,
    std::shared_ptr<std_srvs::srv::Trigger::Response> response
  );
  rclcpp::CallbackGroup::SharedPtr cb_trigger_;


  // Service to trigger the activation
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr trigger_srv_;
  // Nodes managed by this manager
  std::vector<std::string> managed_nodes_;
  // Client used to change the state of the managed nodes
  std::map<std::string, ChangeStateClient::SharedPtr> change_state_clients_;
};

} // namespace lifecycle_homework

#endif // !LIFECYCLE_HOMEWORK__MANAGED_NODE_HPP_
