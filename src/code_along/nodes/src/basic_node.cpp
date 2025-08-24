#include <rclcpp/rclcpp.hpp>

namespace my_component
{
class MyClass : public rclcpp::Node
{
public:
  MyClass(const rclcpp::NodeOptions & options)
  : Node("my_node", options)
  {
    RCLCPP_INFO(this->get_logger(), "Node has been started.");
  }
};
}

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(my_component::MyClass)
