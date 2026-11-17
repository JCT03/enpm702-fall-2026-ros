#include "l11_robotaxi/controller_node.hpp"

#include <chrono>
#include <iomanip>
#include <thread>

namespace l11_robotaxi {

void ControllerNode::command_callback(const std_msgs::msg::Float64 &msg) {
    distance_ = msg.data;
    last_reading_ = now();
    // TODO: uncomment the next line: 1.4 s of work.
    // std::this_thread::sleep_for(std::chrono::milliseconds{1400});
    geometry_msgs::msg::Twist command{};
    // Full speed far from the cone, slow down within 8 m, stop within 5 m.
    if (distance_ > 8.0) {
        command.linear.x = 2.0;
    } else if (distance_ > 5.0) {
        command.linear.x = 1.0;
    } else {
        command.linear.x = 0.0;
    }
    publisher_->publish(command);
    RCLCPP_INFO_STREAM(get_logger(), color::command_callback << "command_callback" << color::reset
                                         << ": cone at " << distance_
                                         << " m, speed " << command.linear.x << " m/s");
}

void ControllerNode::watchdog_callback() {
    const double age{(now() - last_reading_).seconds()};
    if (age > 1.0) {
        // No distance for more than 1 s: stop the robotaxi.
        publisher_->publish(geometry_msgs::msg::Twist{});
        RCLCPP_WARN_STREAM(get_logger(), color::watchdog_callback << "watchdog_callback" << color::reset
                                             << ": no reading for "
                                             << std::fixed << std::setprecision(2) << age
                                             << " s, stop");
        return;
    }
    RCLCPP_INFO_STREAM(get_logger(), color::watchdog_callback << "watchdog_callback" << color::reset
                                         << ": last reading "
                                         << std::fixed << std::setprecision(2) << age << " s ago");
}

} // namespace l11_robotaxi
