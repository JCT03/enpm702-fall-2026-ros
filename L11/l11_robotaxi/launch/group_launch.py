from launch import LaunchDescription
from launch.actions import GroupAction
from launch_ros.actions import Node, PushROSNamespace


def make_taxi(namespace):
    return GroupAction(
        [
            PushROSNamespace(namespace),
            Node(package="l11_robotaxi", executable="robotaxi_exe"),
            Node(package="l11_robotaxi", executable="dispatcher_exe"),
        ]
    )


def generate_launch_description():
    ld = LaunchDescription()
    ld.add_action(make_taxi("taxi1"))
    ld.add_action(make_taxi("taxi2"))
    return ld
