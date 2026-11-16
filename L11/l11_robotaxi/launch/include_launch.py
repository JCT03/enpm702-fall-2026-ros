from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    ld = LaunchDescription()
    demo_share = FindPackageShare("demo_nodes_cpp")
    talker_listener_file = PathJoinSubstitution(
        [demo_share, "launch", "topics", "talker_listener_launch.py"]
    )
    robotaxi = Node(package="l11_robotaxi", executable="robotaxi_exe")
    talker_listener = IncludeLaunchDescription(talker_listener_file)
    ld.add_action(robotaxi)
    ld.add_action(talker_listener)
    return ld
