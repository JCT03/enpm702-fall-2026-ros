from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, GroupAction
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node, PushROSNamespace


def make_taxi(namespace, condition=None):
    return GroupAction(
        [
            PushROSNamespace(namespace),
            Node(package="l11_robotaxi", executable="robotaxi_exe"),
            Node(package="l11_robotaxi", executable="dispatcher_exe"),
        ],
        condition=condition,
    )


def generate_launch_description():
    ld = LaunchDescription()
    two_taxis = DeclareLaunchArgument(
        "two_taxis",
        default_value="false",
        description="Start a second robotaxi in taxi2",
    )
    second = IfCondition(LaunchConfiguration("two_taxis"))
    ld.add_action(two_taxis)
    ld.add_action(make_taxi("taxi1"))
    ld.add_action(make_taxi("taxi2", second))
    return ld
