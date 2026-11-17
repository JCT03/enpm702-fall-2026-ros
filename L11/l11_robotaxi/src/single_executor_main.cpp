#include <memory>

#include <rclcpp/rclcpp.hpp>

#include "l11_robotaxi/camera_node.hpp"
#include "l11_robotaxi/controller_node.hpp"

// Two nodes, one single-threaded executor, one thread.
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto camera{std::make_shared<l11_robotaxi::CameraNode>()};
    auto controller{std::make_shared<l11_robotaxi::ControllerNode>()};
    rclcpp::executors::SingleThreadedExecutor executor{};
    executor.add_node(camera);
    executor.add_node(controller);
    executor.spin();
    if (rclcpp::ok()) {
        rclcpp::shutdown();
    }
}
