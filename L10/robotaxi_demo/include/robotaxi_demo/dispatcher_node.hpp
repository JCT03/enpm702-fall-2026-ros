#pragma once
#include <functional>
#include <geometry_msgs/msg/point.hpp>
#include <rclcpp/rclcpp.hpp>

namespace robotaxi_demo {

class DispatcherNode : public rclcpp::Node {
 public:
  DispatcherNode()
      : rclcpp::Node{"dispatcher_node"},
        subscription_{create_subscription<geometry_msgs::msg::Point>(
            "robotaxi/position", 10,
            std::bind(&DispatcherNode::on_position, this,
                      std::placeholders::_1))} {}
 private:
  void on_position(const geometry_msgs::msg::Point& msg);
  rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr subscription_;
  double pickup_x_{10.0};  // pickup point, in m
  double pickup_y_{0.0};   // pickup point, in m
};

}  // namespace robotaxi_demo
