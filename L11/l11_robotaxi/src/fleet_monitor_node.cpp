#include "l11_robotaxi/fleet_monitor_node.hpp"

#include <string>

using l11_robotaxi_interfaces::msg::RobotaxiStatus;

namespace l11_robotaxi {

void FleetMonitorNode::on_status(const RobotaxiStatus &msg) {
    std::string mode{"unknown"};
    if (msg.mode == RobotaxiStatus::MODE_IDLE) {
        mode = "idle";
    } else if (msg.mode == RobotaxiStatus::MODE_EN_ROUTE) {
        mode = "en route";
    } else if (msg.mode == RobotaxiStatus::MODE_PICKING_UP) {
        mode = "picking up";
    } else if (msg.mode == RobotaxiStatus::MODE_CHARGING) {
        mode = "charging";
    }
    RCLCPP_INFO_STREAM(get_logger(), "on_status: " << msg.robotaxi_name << " " << mode
                                         << " at x = " << msg.position.x << " m, "
                                         << msg.battery << " %");
}

} // namespace l11_robotaxi
