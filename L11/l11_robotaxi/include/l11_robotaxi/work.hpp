#pragma once
#include <chrono>
#include <string>
#include <thread>

#include <rclcpp/rclcpp.hpp>

#include "l11_robotaxi/colors.hpp"

namespace l11_robotaxi {

// Stands in for 0.3 s of real work (reading a sensor, checking a part):
// logs when the callback starts and when it ends, its name in `color`.
inline void work(const rclcpp::Logger &logger, const std::string &callback, const char *color) {
    RCLCPP_INFO_STREAM(logger, color << callback << color::reset << " start");
    std::this_thread::sleep_for(std::chrono::milliseconds{300});
    RCLCPP_INFO_STREAM(logger, color << callback << color::reset << " end");
}

} // namespace l11_robotaxi
