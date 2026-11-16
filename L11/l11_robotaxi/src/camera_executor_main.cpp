#include <memory>

#include <rclcpp/rclcpp.hpp>

#include "l11_robotaxi/camera_node.hpp"

// The same as camera_main.cpp, with rclcpp::spin(node) written out.
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node{std::make_shared<l11_robotaxi::CameraNode>()};
    rclcpp::executors::SingleThreadedExecutor executor{};
    executor.add_node(node);
    executor.spin();
    if (rclcpp::ok()) {
        rclcpp::shutdown();
    }
}
