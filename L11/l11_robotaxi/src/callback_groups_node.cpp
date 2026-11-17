#include "l11_robotaxi/callback_groups_node.hpp"

#include <thread>

#include "l11_robotaxi/colors.hpp"

namespace l11_robotaxi {

// The slow callbacks: log, work for 1.5 s, log again. Each callback's name
// is printed in its own color (colors.hpp), so its lines stand out in the
// terminal.
void CallbackGroupsNode::slow_work(const std::string &name, const char *color) {
    RCLCPP_INFO_STREAM(get_logger(), color << name << color::reset << " start");
    std::this_thread::sleep_for(std::chrono::milliseconds{1500});
    RCLCPP_INFO_STREAM(get_logger(), color << name << color::reset << " end");
}

void CallbackGroupsNode::timer1_callback() { slow_work("timer1", color::timer1); }

void CallbackGroupsNode::timer2_callback() {
    RCLCPP_INFO_STREAM(get_logger(), color::timer2 << "timer2" << color::reset);
}

void CallbackGroupsNode::timer3_callback() { slow_work("timer3", color::timer3); }

void CallbackGroupsNode::timer4_callback() {
    RCLCPP_INFO_STREAM(get_logger(), color::timer4 << "timer4" << color::reset);
}

} // namespace l11_robotaxi
