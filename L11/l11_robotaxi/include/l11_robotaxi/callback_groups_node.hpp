#pragma once
#include <chrono>
#include <functional>
#include <string>
#include <rclcpp/rclcpp.hpp>

namespace l11_robotaxi {

// Four timers in two callback groups. In each group, the first timer's
// callback is slow (1.5 s of work, every 1 s) and the second is fast
// (no work, every 0.5 s).
class CallbackGroupsNode : public rclcpp::Node {
  public:
    CallbackGroupsNode(rclcpp::CallbackGroupType group1_type,
                       rclcpp::CallbackGroupType group2_type)
        : rclcpp::Node{"callback_groups_node"},
          group1_{create_callback_group(group1_type)},
          group2_{create_callback_group(group2_type)},
          timer1_{create_wall_timer(
              std::chrono::milliseconds{1000},
              std::bind(&CallbackGroupsNode::timer1_callback, this),
              group1_)},
          timer2_{create_wall_timer(
              std::chrono::milliseconds{500},
              std::bind(&CallbackGroupsNode::timer2_callback, this),
              group1_)},
          timer3_{create_wall_timer(
              std::chrono::milliseconds{1000},
              std::bind(&CallbackGroupsNode::timer3_callback, this),
              group2_)},
          timer4_{create_wall_timer(
              std::chrono::milliseconds{500},
              std::bind(&CallbackGroupsNode::timer4_callback, this),
              group2_)} {}

  private:
    void timer1_callback();
    void timer2_callback();
    void timer3_callback();
    void timer4_callback();
    void slow_work(const std::string &name, const char *color);
    rclcpp::CallbackGroup::SharedPtr group1_;
    rclcpp::CallbackGroup::SharedPtr group2_;
    rclcpp::TimerBase::SharedPtr timer1_;
    rclcpp::TimerBase::SharedPtr timer2_;
    rclcpp::TimerBase::SharedPtr timer3_;
    rclcpp::TimerBase::SharedPtr timer4_;
};

} // namespace l11_robotaxi
