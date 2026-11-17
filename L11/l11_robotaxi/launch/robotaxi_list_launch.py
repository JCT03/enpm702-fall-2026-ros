from launch import LaunchDescription
from launch_ros.actions import Node


# The same two nodes as robotaxi_launch.py, given as one list.
def generate_launch_description():
    return LaunchDescription(
        [
            Node(package="l11_robotaxi", executable="robotaxi_exe"),
            Node(package="l11_robotaxi", executable="dispatcher_exe"),
        ]
    )
