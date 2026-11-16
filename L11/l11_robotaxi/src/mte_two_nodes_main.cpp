#include <memory>

#include <rclcpp/rclcpp.hpp>

#include "l11_robotaxi/health_node.hpp"
#include "l11_robotaxi/sensors_node.hpp"

// Two nodes with three timers each in a multi-threaded executor with three
// threads.
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto sensors{std::make_shared<l11_robotaxi::SensorsNode>()};
    auto health{std::make_shared<l11_robotaxi::HealthNode>()};
    rclcpp::executors::MultiThreadedExecutor executor{
        rclcpp::ExecutorOptions{}, 3};
    executor.add_node(sensors);
    executor.add_node(health);
    executor.spin();
    if (rclcpp::ok()) {
        rclcpp::shutdown();
    }
}
