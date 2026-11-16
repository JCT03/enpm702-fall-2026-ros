#include "l11_robotaxi/robotaxi_node.hpp"

namespace l11_robotaxi {

void RoboTaxiNode::publish_position() {
    geometry_msgs::msg::Point msg{}; // x, y and z start at 0.0
    msg.x = x_;
    publisher_->publish(msg);
    RCLCPP_INFO_STREAM(get_logger(), "Published x = " << msg.x);
    x_ += 1.0; // 1 m every 0.5 s: 2 m/s
}

} // namespace l11_robotaxi
