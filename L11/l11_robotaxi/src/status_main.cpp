#include <memory>

#include <rclcpp/rclcpp.hpp>

#include "l11_robotaxi/status_node.hpp"

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node{std::make_shared<l11_robotaxi::StatusNode>()};
    rclcpp::spin(node);
    if (rclcpp::ok()) {
        rclcpp::shutdown();
    }
}
