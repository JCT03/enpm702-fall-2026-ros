#include "l11_robotaxi/status_node.hpp"

using l11_robotaxi_interfaces::msg::RobotaxiStatus;

namespace l11_robotaxi {

void StatusNode::publish_status() {
    RobotaxiStatus msg{};
    msg.header.stamp = now();
    msg.header.frame_id = "map";
    msg.robotaxi_name = "robotaxi_1";
    // The rider waits 3 m ahead: drive 1 m per status until there.
    if (x_ < 3.0) {
        x_ += 1.0;
        msg.mode = RobotaxiStatus::MODE_EN_ROUTE;
    } else {
        msg.mode = RobotaxiStatus::MODE_PICKING_UP;
    }
    msg.position.x = x_;
    battery_ -= 0.5F;
    msg.battery = battery_;
    publisher_->publish(msg);
    RCLCPP_INFO_STREAM(get_logger(), "publish_status: x = " << msg.position.x
                                         << " m, battery " << msg.battery << " %");
}

} // namespace l11_robotaxi
