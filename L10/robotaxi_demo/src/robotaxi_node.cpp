#include "robotaxi_demo/robotaxi_node.hpp"

namespace robotaxi_demo {

void RoboTaxiNode::publish_position() {
    geometry_msgs::msg::Point pos_msg{}; // x, y and z start at 0.0
    pos_msg.x = x_;
    position_publisher_->publish(pos_msg);
    RCLCPP_INFO_STREAM(get_logger(), "Published x = " << pos_msg.x);
    x_ += 1.0; // 1 m every 0.5 s: 2 m/s

    std_msgs::msg::Float64 bat_msg{};
    bat_msg.data = battery_;
    battery_publisher_->publish(bat_msg);
    RCLCPP_INFO_STREAM(get_logger(), "Published charge = " << bat_msg.data);
    battery_ -= 0.5; // 0.5% every s
}

} // namespace robotaxi_demo
