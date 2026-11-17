#pragma once
#include <chrono>
#include <functional>
#include <rclcpp/rclcpp.hpp>

namespace l11_robotaxi {

// The robotaxi's other sensors: every 1 s, one timer per sensor reads the
// lidar, the radar and the GPS. Each reading takes 0.3 s.
class SensorsNode : public rclcpp::Node {
  public:
    SensorsNode()
        : rclcpp::Node{"sensors_node"},
          lidar_timer_{create_wall_timer(std::chrono::milliseconds{1000},
                                         std::bind(&SensorsNode::lidar_callback, this))},
          radar_timer_{create_wall_timer(std::chrono::milliseconds{1000},
                                         std::bind(&SensorsNode::radar_callback, this))},
          gps_timer_{create_wall_timer(std::chrono::milliseconds{1000},
                                       std::bind(&SensorsNode::gps_callback, this))} {}

  private:
    void lidar_callback();
    void radar_callback();
    void gps_callback();
    rclcpp::TimerBase::SharedPtr lidar_timer_;
    rclcpp::TimerBase::SharedPtr radar_timer_;
    rclcpp::TimerBase::SharedPtr gps_timer_;
};

} // namespace l11_robotaxi
