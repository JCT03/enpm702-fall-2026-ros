#include "l11_robotaxi/health_node.hpp"

#include "l11_robotaxi/work.hpp"

namespace l11_robotaxi {

void HealthNode::battery_callback() { work(get_logger(), "battery_callback", color::health_node); }

void HealthNode::tire_callback() { work(get_logger(), "tire_callback", color::health_node); }

void HealthNode::door_callback() { work(get_logger(), "door_callback", color::health_node); }

} // namespace l11_robotaxi
