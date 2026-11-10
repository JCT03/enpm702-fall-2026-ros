#pragma once
#include <chrono>
#include <functional>
#include <geometry_msgs/msg/point.hpp>
#include <rclcpp/rclcpp.hpp>

namespace robotaxi_demo {

class RoboTaxiNode : public rclcpp::Node {
  public:
    RoboTaxiNode() : rclcpp::Node{"robotaxi_node"} {
        RCLCPP_INFO_STREAM(get_logger(), get_name() << " is ready");
        // RCLCPP_WARN_STREAM(get_logger(), get_name() << " is ready");
        // RCLCPP_ERROR_STREAM(get_logger(), get_name() << " is ready");
        // RCLCPP_FATAL_STREAM(get_logger(), get_name() << " is ready");
    }
    // RoboTaxiNode()
    //     : rclcpp::Node{"robotaxi_node"},
    //       publisher_{create_publisher<geometry_msgs::msg::Point>("robotaxi/position", 10)},
    //       timer_{create_wall_timer(std::chrono::milliseconds{500},
    //                                std::bind(&RoboTaxiNode::publish_position, this))} {
    // }

  private:
    // void publish_position();
    // rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr publisher_;
    // rclcpp::TimerBase::SharedPtr timer_;
    // double x_{0.0}; // position along the street, in m
};

} // namespace robotaxi_demo
