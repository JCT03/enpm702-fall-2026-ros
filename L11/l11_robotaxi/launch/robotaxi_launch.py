from launch import LaunchDescription
from launch_ros.actions import Node


# ros2 launch calls this function and starts the actions it returns.
def generate_launch_description():
    ld = LaunchDescription()
    robotaxi = Node(package="l11_robotaxi", executable="robotaxi_exe")
    dispatcher = Node(
        package="l11_robotaxi", executable="dispatcher_exe"
    )
    ld.add_action(robotaxi)
    ld.add_action(dispatcher)
    return ld
