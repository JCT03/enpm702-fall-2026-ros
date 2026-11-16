#include <memory>

#include <rclcpp/rclcpp.hpp>

#include "l11_robotaxi/callback_groups_node.hpp"

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    using Type = rclcpp::CallbackGroupType;
    auto node{std::make_shared<l11_robotaxi::CallbackGroupsNode>(
        Type::MutuallyExclusive, Type::MutuallyExclusive)};
    // 6 threads: enough that no callback ever waits for a free thread.
    rclcpp::executors::MultiThreadedExecutor executor{
        rclcpp::ExecutorOptions{}, 6};
    executor.add_node(node);
    executor.spin();
    if (rclcpp::ok()) {
        rclcpp::shutdown();
    }
}
