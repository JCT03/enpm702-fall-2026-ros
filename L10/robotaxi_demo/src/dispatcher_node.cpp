#include "robotaxi_demo/dispatcher_node.hpp"

#include <cmath>

namespace robotaxi_demo {

void DispatcherNode::on_position(const geometry_msgs::msg::Point& msg) {
  const double distance{
      std::hypot(pickup_x_ - msg.x, pickup_y_ - msg.y)};
  RCLCPP_INFO_STREAM(get_logger(), distance << " m from the pickup");
}

}  // namespace robotaxi_demo
