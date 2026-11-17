from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, LogInfo
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    ld = LaunchDescription()
    with_dispatcher = DeclareLaunchArgument(
        "with_dispatcher",
        default_value="true",
        description="Start the dispatcher node too",
    )
    robotaxi = Node(package="l11_robotaxi", executable="robotaxi_exe")
    dispatcher = Node(
        package="l11_robotaxi",
        executable="dispatcher_exe",
        condition=IfCondition(LaunchConfiguration("with_dispatcher")),
    )
    ld.add_action(with_dispatcher)
    ld.add_action(robotaxi)
    ld.add_action(dispatcher)
    log_value = LogInfo(
        msg=[
            "with_dispatcher = ",
            LaunchConfiguration("with_dispatcher"),
        ]
    )
    ld.add_action(log_value)
    return ld
