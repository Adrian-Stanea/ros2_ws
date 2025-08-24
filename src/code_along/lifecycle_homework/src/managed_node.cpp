#include "lifecycle_homework/managed_node.hpp"

namespace lifecycle_homework
{

using CallbackReturn = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

ManagedNode::ManagedNode(const rclcpp::NodeOptions & options)
: rclcpp_lifecycle::LifecycleNode("managed_node", options) {}

CallbackReturn ManagedNode::on_configure(const rclcpp_lifecycle::State & previous_state)
{
  RCLCPP_INFO(this->get_logger(), "Configured");
  return CallbackReturn::SUCCESS;
}

CallbackReturn ManagedNode::on_activate(const rclcpp_lifecycle::State & previous_state)
{
  RCLCPP_INFO(this->get_logger(), "Activated");
  return CallbackReturn::SUCCESS;
}

CallbackReturn ManagedNode::on_deactivate(const rclcpp_lifecycle::State & previous_state)
{
  RCLCPP_INFO(this->get_logger(), "Deactivated");
  return CallbackReturn::SUCCESS;
}

CallbackReturn ManagedNode::on_cleanup(const rclcpp_lifecycle::State & previous_state)
{
  RCLCPP_INFO(this->get_logger(), "Cleaned up");
  return CallbackReturn::SUCCESS;
}

CallbackReturn ManagedNode::on_shutdown(const rclcpp_lifecycle::State & previous_state)
{
  RCLCPP_INFO(this->get_logger(), "Shut down");
  return CallbackReturn::SUCCESS;
}

CallbackReturn ManagedNode::on_error(const rclcpp_lifecycle::State & previous_state)
{
  RCLCPP_INFO(this->get_logger(), "Error occurred");
  return CallbackReturn::SUCCESS;
}

}

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(lifecycle_homework::ManagedNode)
