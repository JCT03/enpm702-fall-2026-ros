#include "robotaxi_demo/battery_monitor_node.hpp"

namespace robotaxi_demo {

void BatteryMonitorNode::on_battery(const std_msgs::msg::Float64 &msg) {
    const double battery{msg.data};
    if (battery >= 20.0) {
        RCLCPP_INFO_STREAM(get_logger(), "battery at " << battery << '%');
    } else {
        RCLCPP_WARN_STREAM(get_logger(), "battery at " << battery << '%');
    }
}

} // namespace robotaxi_demo
