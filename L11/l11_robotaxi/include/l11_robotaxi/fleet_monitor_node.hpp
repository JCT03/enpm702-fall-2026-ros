#pragma once
#include <functional>
#include <l11_robotaxi_interfaces/msg/robotaxi_status.hpp>
#include <rclcpp/rclcpp.hpp>

namespace l11_robotaxi {

// Runs at the depot: on_status runs each time a robotaxi status arrives on
// /robotaxi/status and logs it, the mode as text.
class FleetMonitorNode : public rclcpp::Node {
  public:
    FleetMonitorNode()
        : rclcpp::Node{"fleet_monitor_node"},
          subscription_{create_subscription<l11_robotaxi_interfaces::msg::RobotaxiStatus>(
              "robotaxi/status", 10,
              std::bind(&FleetMonitorNode::on_status, this, std::placeholders::_1))} {}

  private:
    void on_status(const l11_robotaxi_interfaces::msg::RobotaxiStatus &msg);
    rclcpp::Subscription<l11_robotaxi_interfaces::msg::RobotaxiStatus>::SharedPtr subscription_;
};

} // namespace l11_robotaxi
