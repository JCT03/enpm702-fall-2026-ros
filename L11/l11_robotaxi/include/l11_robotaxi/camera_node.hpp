#pragma once
#include <chrono>
#include <functional>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64.hpp>

#include "l11_robotaxi/colors.hpp"

namespace l11_robotaxi {

// Stands in for the robotaxi's front camera: every 0.5 s, sensor_callback
// publishes the distance to the traffic cone ahead; every 1 s,
// health_callback reports how many readings the camera took since its last
// check.
class CameraNode : public rclcpp::Node {
  public:
    CameraNode()
        : rclcpp::Node{"camera_node"},
          publisher_{create_publisher<std_msgs::msg::Float64>("camera/cone_distance", 10)},
          sensor_timer_{create_wall_timer(std::chrono::milliseconds{500},
                                          std::bind(&CameraNode::sensor_callback, this))},
          health_timer_{create_wall_timer(std::chrono::milliseconds{1000},
                                          std::bind(&CameraNode::health_callback, this))} {}

  private:
    void sensor_callback();
    void health_callback();
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr sensor_timer_;
    rclcpp::TimerBase::SharedPtr health_timer_;
    double distance_{10.0}; // distance to the cone, in m
    int readings_{0};       // readings since the last health check
};

} // namespace l11_robotaxi
