#include <memory>

#include <rclcpp/rclcpp.hpp>

#include "robotaxi_demo/dispatcher_node.hpp"

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node{std::make_shared<robotaxi_demo::DispatcherNode>()};
    rclcpp::spin(node);
    rclcpp::shutdown();
}
