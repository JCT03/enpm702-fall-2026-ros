#include "l11_robotaxi/camera_node.hpp"

namespace l11_robotaxi {

void CameraNode::sensor_callback() {
    std_msgs::msg::Float64 msg{};
    msg.data = distance_;
    publisher_->publish(msg);
    ++readings_;
    RCLCPP_INFO_STREAM(get_logger(), color::sensor_callback << "sensor_callback" << color::reset
                                         << ": cone at " << distance_ << " m");
    // The robotaxi gets 1 m closer per reading, until the controller stops it 5 m
    // from the cone.
    if (distance_ > 5.0) {
        distance_ -= 1.0;
    }
}

void CameraNode::health_callback() {
    RCLCPP_INFO_STREAM(get_logger(), color::health_callback << "health_callback" << color::reset
                                         << ": readings since the last check = "
                                         << readings_);
    readings_ = 0;
}

} // namespace l11_robotaxi
