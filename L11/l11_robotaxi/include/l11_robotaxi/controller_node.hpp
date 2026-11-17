#pragma once
#include <chrono>
#include <functional>
#include <geometry_msgs/msg/twist.hpp>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64.hpp>

#include "l11_robotaxi/colors.hpp"

namespace l11_robotaxi {

// Decides the robotaxi's speed: command_callback runs each time a distance
// to the cone arrives, stores it, and publishes a speed command. Every 1 s,
// watchdog_callback stops the robotaxi if no distance arrived for more than
// 1 s. A 1.4 s delay in command_callback, commented out in
// controller_node.cpp, is for the class to turn on.
class ControllerNode : public rclcpp::Node {
  public:
    ControllerNode()
        : rclcpp::Node{"controller_node"},
          subscription_{create_subscription<std_msgs::msg::Float64>(
              "camera/cone_distance", 10,
              std::bind(&ControllerNode::command_callback, this, std::placeholders::_1))},
          publisher_{create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10)},
          watchdog_timer_{create_wall_timer(std::chrono::milliseconds{1000},
                                            std::bind(&ControllerNode::watchdog_callback, this))},
          last_reading_{now()} {}

  private:
    void command_callback(const std_msgs::msg::Float64 &msg);
    void watchdog_callback();
    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr watchdog_timer_;
    rclcpp::Time last_reading_; // when the last distance arrived
    double distance_{0.0};      // last distance to the cone, in m
};

} // namespace l11_robotaxi
