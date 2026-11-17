#include <memory>

#include <rclcpp/rclcpp.hpp>

#include "l11_robotaxi/camera_node.hpp"
#include "l11_robotaxi/controller_node.hpp"

// Does not work: the first rclcpp::spin returns only after Ctrl+C, so the
// controller's callbacks never run. single_executor_main.cpp is the fix.
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto camera{std::make_shared<l11_robotaxi::CameraNode>()};
    auto controller{std::make_shared<l11_robotaxi::ControllerNode>()};
    rclcpp::spin(camera);
    rclcpp::spin(controller);
    if (rclcpp::ok()) {
        rclcpp::shutdown();
    }
}
