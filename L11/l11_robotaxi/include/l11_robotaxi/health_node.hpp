#pragma once
#include <chrono>
#include <functional>
#include <rclcpp/rclcpp.hpp>

namespace l11_robotaxi {

// Checks the robotaxi's parts: every 1 s, one timer per part checks the
// battery, the tires and the doors. Each check takes 0.3 s.
class HealthNode : public rclcpp::Node {
  public:
    HealthNode()
        : rclcpp::Node{"health_node"},
          battery_timer_{create_wall_timer(std::chrono::milliseconds{1000},
                                           std::bind(&HealthNode::battery_callback, this))},
          tire_timer_{create_wall_timer(std::chrono::milliseconds{1000},
                                        std::bind(&HealthNode::tire_callback, this))},
          door_timer_{create_wall_timer(std::chrono::milliseconds{1000},
                                        std::bind(&HealthNode::door_callback, this))} {}

  private:
    void battery_callback();
    void tire_callback();
    void door_callback();
    rclcpp::TimerBase::SharedPtr battery_timer_;
    rclcpp::TimerBase::SharedPtr tire_timer_;
    rclcpp::TimerBase::SharedPtr door_timer_;
};

} // namespace l11_robotaxi
