#pragma once
#include <chrono>
#include <functional>
#include <geometry_msgs/msg/point.hpp>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64.hpp>

namespace robotaxi_demo {

class RoboTaxiNode : public rclcpp::Node {
  public:
    // RoboTaxiNode() : rclcpp::Node{"robotaxi_node"} {
    //     RCLCPP_INFO_STREAM(get_logger(), get_name() << " is ready");
    //     RCLCPP_WARN_STREAM(get_logger(), get_name() << " is ready");
    //     RCLCPP_ERROR_STREAM(get_logger(), get_name() << " is ready");
    //     RCLCPP_FATAL_STREAM(get_logger(), get_name() << " is ready");
    // }
    RoboTaxiNode()
        : rclcpp::Node{"robotaxi_node"},
          position_publisher_{create_publisher<geometry_msgs::msg::Point>("robotaxi/position", 10)},
          battery_publisher_{create_publisher<std_msgs::msg::Float64>("robotaxi/battery", 10)},
          timer_{create_wall_timer(std::chrono::milliseconds{500},
                                   std::bind(&RoboTaxiNode::publish_position, this))} {
    }

  private:
    void publish_position();
    rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr position_publisher_;
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr battery_publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    double x_{0.0}; // position along the street, in m
    double battery_{100.0}; // battery charge, in percent
};

} // namespace robotaxi_demo
