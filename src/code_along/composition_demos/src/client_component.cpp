#include "composition_demos/client_component.hpp"

#include <cinttypes>
#include <memory>
#include <iostream>

#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

namespace composition_demos
{

using namespace std::chrono_literals;
using AddTwoIntsSrv = example_interfaces::srv::AddTwoInts;

Client::Client(const rclcpp::NodeOptions & options)
: Node("client", options)
{
  client_ = create_client<AddTwoIntsSrv>("add_two_ints");
  timer_ = create_wall_timer(1s, std::bind(&Client::on_timer, this));
}

void Client::on_timer()
{
  if (!client_->wait_for_service(400ms)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(get_logger(), "Interrupted while waiting for the service. Exiting.");
      return;
    }
    RCLCPP_INFO(get_logger(), "Service not available after waiting");
    return;
  }

  auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
  request->a = 2;
  request->b = 3;

  using ServiceResponseFuture = rclcpp::Client<AddTwoIntsSrv>::SharedFuture;
  auto response_received_callback = [this](ServiceResponseFuture future) {
      RCLCPP_INFO(this->get_logger(), "Got result: [%" PRId64 "]", future.get()->sum);
    };
  auto future_result = client_->async_send_request(request, response_received_callback);
}

} // namespace composition_demos

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(composition_demos::Client)
