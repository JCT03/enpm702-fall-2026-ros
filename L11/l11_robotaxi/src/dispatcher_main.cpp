#include <memory>

#include <rclcpp/rclcpp.hpp>

#include "l11_robotaxi/dispatcher_node.hpp"

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node{std::make_shared<l11_robotaxi::DispatcherNode>()};
    rclcpp::spin(node);
    // After Ctrl+C, the signal handler has already shut ROS 2 down. A second
    // rclcpp::shutdown() would remove that handler, and the Ctrl+C that ros2 launch
    // forwards would then kill the process ("process has died").
    if (rclcpp::ok()) {
        rclcpp::shutdown();
    }
}
