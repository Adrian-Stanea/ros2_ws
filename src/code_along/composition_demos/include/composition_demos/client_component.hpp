#ifndef COMPOSITION_DEMOS__CLIENT_COMPONENT_HPP_
#define COMPOSITION_DEMOS__CLIENT_COMPONENT_HPP_

#include "composition_demos/visibility_control.h"
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

namespace composition_demos
{

using AddTwoIntsSrv = example_interfaces::srv::AddTwoInts;

class Client : public rclcpp::Node
{
public:
  COMPOSITION_PUBLIC
  explicit Client(const rclcpp::NodeOptions & options);

protected:
  void on_timer();

private:
  rclcpp::Client<AddTwoIntsSrv>::SharedPtr client_;
  rclcpp::TimerBase::SharedPtr timer_;
};

} // namespace composition_demos

#endif // !COMPOSITION_DEMOS__CLIENT_COMPONENT_HPP_
