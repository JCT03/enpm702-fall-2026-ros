from launch import LaunchDescription
from launch.actions import LogInfo, RegisterEventHandler
from launch.event_handlers import OnProcessStart, OnShutdown
from launch_ros.actions import Node


def generate_launch_description():
    ld = LaunchDescription()
    robotaxi = Node(package="l11_robotaxi", executable="robotaxi_exe")
    dispatcher = Node(
        package="l11_robotaxi", executable="dispatcher_exe"
    )
    # When the robotaxi starts: log a line, start the dispatcher.
    start_dispatcher = RegisterEventHandler(
        OnProcessStart(
            target_action=robotaxi,
            on_start=[
                LogInfo(msg="robotaxi started, starting dispatcher"),
                dispatcher,
            ],
        )
    )
    # When the launch shuts down (Ctrl+C), log a last line.
    goodbye = RegisterEventHandler(
        OnShutdown(on_shutdown=[LogInfo(msg="Fleet stopped")])
    )
    ld.add_action(robotaxi)
    ld.add_action(start_dispatcher)
    ld.add_action(goodbye)
    return ld
