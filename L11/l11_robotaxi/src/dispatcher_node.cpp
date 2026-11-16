#include "l11_robotaxi/dispatcher_node.hpp"

#include <cmath>

namespace l11_robotaxi {

void DispatcherNode::on_position(const geometry_msgs::msg::Point &msg) {
    const double distance{std::hypot(pickup_x_ - msg.x, pickup_y_ - msg.y)};
    RCLCPP_INFO_STREAM(get_logger(), distance << " m from the pickup");
}

} // namespace l11_robotaxi
