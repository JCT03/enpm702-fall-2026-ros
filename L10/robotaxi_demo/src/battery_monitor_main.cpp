#include <memory>

#include <rclcpp/rclcpp.hpp>

#include "robotaxi_demo/battery_monitor_node.hpp"

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node{std::make_shared<robotaxi_demo::BatteryMonitorNode>()};
    rclcpp::spin(node);
    if (rclcpp::ok()) {
        rclcpp::shutdown();
    }
}
