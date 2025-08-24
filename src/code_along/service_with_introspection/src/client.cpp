#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

static constexpr char const * const SERVICE_NAME = "add_two_ints";

int main(int argc, char const * argv[])
{
  rclcpp::init(argc, argv);

  if (argc != 3) {
    RCLCPP_WARN(rclcpp::get_logger("rclcpp"), "Usage: client X Y");
    return 1;
  }

  auto node = std::make_shared<rclcpp::Node>("add_two_ints_client");

  auto client = node->create_client<example_interfaces::srv::AddTwoInts>(SERVICE_NAME);

  auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
  request->a = atoll(argv[1]);
  request->b = atoll(argv[2]);

  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(
        rclcpp::get_logger("rclcpp"),
        "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(
      rclcpp::get_logger("rclcpp"),
      "service not available, waiting again...");
  }

  auto result = client->async_send_request(request);

  if (rclcpp::spin_until_future_complete(node, result) == rclcpp::FutureReturnCode::SUCCESS) {
    RCLCPP_INFO(
      rclcpp::get_logger("rclcpp"),
      "Sum: %ld", result.get()->sum);
  } else {
    RCLCPP_ERROR(
      rclcpp::get_logger("rclcpp"),
      "Failed to call service add_two_ints");
  }

  rclcpp::shutdown();
  return 0;
}
