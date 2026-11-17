#pragma once
#include <chrono>
#include <functional>
#include <l11_robotaxi_interfaces/msg/robotaxi_status.hpp>
#include <rclcpp/rclcpp.hpp>

namespace l11_robotaxi {

// Runs on the robotaxi: every 1 s, publish_status publishes the robotaxi's
// status (name, mode, position, battery) on /robotaxi/status.
class StatusNode : public rclcpp::Node {
  public:
    StatusNode()
        : rclcpp::Node{"status_node"},
          publisher_{create_publisher<l11_robotaxi_interfaces::msg::RobotaxiStatus>(
              "robotaxi/status", 10)},
          timer_{create_wall_timer(std::chrono::milliseconds{1000},
                                   std::bind(&StatusNode::publish_status, this))} {}

  private:
    void publish_status();
    rclcpp::Publisher<l11_robotaxi_interfaces::msg::RobotaxiStatus>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    double x_{0.0};        // position along the street, in m
    float battery_{80.0F}; // battery level, in percent
};

} // namespace l11_robotaxi
