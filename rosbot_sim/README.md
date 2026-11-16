# rosbot_sim

The simulated Husarion ROSbot for ENPM702 (Lectures 12 to 14 and GP2), and the instructor
package that starts it.

| Folder | What it is | Source |
|---|---|---|
| `gp2_bringup/` | Launch file, worlds and logical camera of the course. Instructor code. | This course |
| `rosbot_ros/` | Packages `rosbot_description`, `rosbot_controller`, `rosbot_gazebo`, `rosbot_localization`, `rosbot_utils` | https://github.com/husarion/rosbot_ros (version 0.18.8), through the instructor's `enpm605-spring-2026-ros` copy |
| `husarion_gz_worlds/` | Gazebo worlds and models | https://github.com/husarion/panther_ros (`husarion_gz_worlds`), same copy |
| `husarion_components_description/` | Descriptions of the sensors on the robot | https://github.com/husarion/husarion_components_description, same copy |

Everything except `gp2_bringup/` is third-party code, changed only as the tables below list. Do not change it. All of it is
Apache License 2.0 (each package keeps its `LICENSE`; `husarion_components_description` also
keeps its `NOTICE.md`).

Setup, launch and a description of the robot and the world:
the course page "ROSbot Simulation" (Setup section).

## What was removed, and why

The upstream packages also drive the real robot, a joystick and a MoveIt arm. The simulation
uses none of that, so it was removed to keep `rosdep install` small. The rosdep keys the
workspace needs on a machine with only `ros-jazzy-desktop`, `ros-jazzy-ros-gz` and
`ros-dev-tools`: 83 before, 35 after.

Packages removed:

| Package | Why it is not needed |
|---|---|
| `rosbot` | Meta-package that lists the real robot's packages. |
| `rosbot_bringup` | Starts the real robot (micro-ROS agent). |
| `rosbot_hardware_interfaces` | ros2_control plugins for the real robot's motor board. The simulation uses `gz_ros2_control`. |
| `rosbot_joy` | Joystick teleoperation (needs MoveIt). |
| `rosbot_moveit` | MoveIt configuration for the robot arm of ROSbot XL. |
| `husarion_controllers/` (`husarion_mecanum_drive_controller`, `twist_mux_controller`, `low_pass_filter`) | Only the mecanum drive of ROSbot XL uses them. The ROSbot has a differential drive. |

Changes inside the kept packages:

| Package | Change |
|---|---|
| `rosbot_utils` | Removed the firmware files and the scripts `flash_firmware`, `flash_firmware_uart.py`, `flash_firmware_usb.py` and `utils.py`, and the dependencies `python3-argcomplete`, `python3-ftdi`, `python3-libgpiod`, `python3-pyudev`, `python3-serial`, `python3-sh`, `stm32flash` and `usbutils`. Kept: the laser filter configuration the simulation starts. `CMakeLists.txt` no longer installs the removed files. |
| `rosbot_gazebo` | Removed the `rosbot_joy` include from `launch/spawn_robot.yaml` and the dependency `rosbot_joy`. |
| `rosbot_controller` | Removed the dependencies `husarion_mecanum_drive_controller`, `rosbot_hardware_interfaces`, `rosbot_moveit`, `rosbot_utils` and `udev`. |
| `rosbot_controller` (`config/rosbot/controllers.yaml`) | Set `left_wheel_radius_multiplier` and `right_wheel_radius_multiplier` of the differential drive controller from 0.95 to 1.0. Husarion's file gives 0.95 with the comment "Based on real measurements", from the real robot. The simulated wheel has exactly the radius the controller assumes (0.0425 m), so 0.95 made the odometry 5 % short: in a 3 m test with `cmd_vel`, odometry said 2.919 m while Gazebo's true travel was 3.074 m (ratio 0.950). With 1.0 the two agree (2.932 m and 2.932 m). The yaw is not affected: it comes from the IMU. |
| `rosbot_description` | Removed the dependency `open_manipulator_description` (ROSbot XL only). |
| `husarion_components_description` | Removed the dependencies `realsense2_description`, `robotiq_description`, `ur_description` and `zed_msgs`. The robot's `basic` configuration uses a Slamtec lidar and a Luxonis OAK camera, so `depthai_descriptions` and `nav2_common` stay. |

Consequences: the ROSbot XL model, the `manipulation` configurations and the real robot
do not work from this folder. Files that only they use (for example
`rosbot_controller/launch/manipulator.yaml`, `rosbot_description/urdf/rosbot_xl.urdf.xacro`,
the `ur` and `kinova` files of `husarion_components_description`) were left as they are.

No other third-party file was edited. Check the changes with `git log -p -- rosbot_sim`.
