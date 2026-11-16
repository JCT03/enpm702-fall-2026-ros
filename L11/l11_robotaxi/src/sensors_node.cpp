#include "l11_robotaxi/sensors_node.hpp"

#include "l11_robotaxi/work.hpp"

namespace l11_robotaxi {

void SensorsNode::lidar_callback() { work(get_logger(), "lidar_callback", color::sensors_node); }

void SensorsNode::radar_callback() { work(get_logger(), "radar_callback", color::sensors_node); }

void SensorsNode::gps_callback() { work(get_logger(), "gps_callback", color::sensors_node); }

} // namespace l11_robotaxi
