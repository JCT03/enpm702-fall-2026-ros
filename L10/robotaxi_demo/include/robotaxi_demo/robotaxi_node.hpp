#pragma once
#include <rclcpp/rclcpp.hpp>

namespace robotaxi_demo {

class RoboTaxiNode : public rclcpp::Node {
 public:
  RoboTaxiNode() : rclcpp::Node{"robotaxi_node"} {
    RCLCPP_INFO_STREAM(get_logger(), get_name() << " is ready");
  }
};

}  // namespace robotaxi_demo
