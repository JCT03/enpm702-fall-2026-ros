#pragma once
#include <functional>
#include <std_msgs/msg/float64.hpp>
#include <rclcpp/rclcpp.hpp>

namespace robotaxi_demo {

class BatteryMonitorNode : public rclcpp::Node {
  public:
    BatteryMonitorNode()
        : rclcpp::Node{"battery_monitor_node"},
          subscription_{create_subscription<std_msgs::msg::Float64>(
              "robotaxi/battery", 10,
              std::bind(&BatteryMonitorNode::on_battery, this,
                        std::placeholders::_1))} {}
  private:
    void on_battery(const std_msgs::msg::Float64 &msg);
    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_;
};

} // namespace robotaxi_demo
