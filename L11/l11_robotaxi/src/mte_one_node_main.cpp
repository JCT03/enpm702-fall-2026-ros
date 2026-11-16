#include <memory>

#include <rclcpp/rclcpp.hpp>

#include "l11_robotaxi/sensors_node.hpp"

// One node with three timers in a multi-threaded executor with three threads.
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto sensors{std::make_shared<l11_robotaxi::SensorsNode>()};
    rclcpp::executors::MultiThreadedExecutor executor{
        rclcpp::ExecutorOptions{}, 3};
    executor.add_node(sensors);
    executor.spin();
    if (rclcpp::ok()) {
        rclcpp::shutdown();
    }
}
