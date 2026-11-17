#include <memory>

#include <rclcpp/rclcpp.hpp>

#include "robotaxi_demo/robotaxi_node.hpp"

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node{std::make_shared<robotaxi_demo::RoboTaxiNode>()};
    rclcpp::spin(node);
    RCLCPP_INFO(node->get_logger(), "exited the loop...");
    // After Ctrl+C, the signal handler has already shut ROS 2 down. A second
    // rclcpp::shutdown() would remove that handler, and the Ctrl+C that ros2 launch
    // forwards would then kill the process ("process has died").
    if (rclcpp::ok()) {
        rclcpp::shutdown();
    }
}
