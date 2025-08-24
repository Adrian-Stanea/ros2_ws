#include "example_interfaces/srv/add_two_ints.hpp"
#include "rclcpp/rclcpp.hpp"

#include <memory>

static constexpr char const * const SERVICE_NAME = "add_two_ints";

void add(
  const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
  std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response
)
{
  response->sum = request->a + request->b;
  RCLCPP_INFO(
    rclcpp::get_logger("rclcpp"),
    "Incoming Request\n a: %ld" " b: %ld", request->a, request->b
  );
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Sending back response: [%ld]", response->sum);
}

int main(int argc, char const *argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<rclcpp::Node>("add_two_ints_server");

  auto service = node->create_service<example_interfaces::srv::AddTwoInts>(SERVICE_NAME, &add);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add two ints.");

  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}

