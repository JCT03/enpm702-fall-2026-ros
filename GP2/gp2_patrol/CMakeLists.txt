cmake_minimum_required(VERSION 3.8)
project(gp2_patrol)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# -Wall -Wextra: the common warnings; -pedantic-errors: code that is not standard C++
# is an error; -Wshadow: a name that hides another one.
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -pedantic-errors -Wshadow)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(ros_gz_interfaces REQUIRED)
# TODO (R1): uncomment once gp2_interfaces builds with your interfaces.
# find_package(gp2_interfaces REQUIRED)

include_directories(include)

# TODO (R3): needs patrol_status_main.cpp and patrol_status_node.cpp.
# add_executable(patrol_status_exe src/patrol_status_main.cpp
#   src/patrol_status_node.cpp)
# ament_target_dependencies(patrol_status_exe rclcpp gp2_interfaces)

# TODO (R3): needs operator_main.cpp and operator_node.cpp.
# add_executable(operator_exe src/operator_main.cpp src/operator_node.cpp)
# ament_target_dependencies(operator_exe rclcpp gp2_interfaces)

# TODO (R4): needs controller_main.cpp and controller_node.cpp.
# add_executable(controller_exe src/controller_main.cpp src/controller_node.cpp)
# ament_target_dependencies(controller_exe rclcpp geometry_msgs nav_msgs
#   sensor_msgs std_msgs gp2_interfaces)

# TODO (R6): needs mission_main.cpp, mission_node.cpp and patrol_log_node.cpp.
# R10 adds the camera: tf2_ros, tf2_geometry_msgs and ros_gz_interfaces.
# add_executable(mission_exe src/mission_main.cpp src/mission_node.cpp
#   src/patrol_log_node.cpp)
# ament_target_dependencies(mission_exe rclcpp geometry_msgs sensor_msgs std_msgs
#   tf2_ros tf2_geometry_msgs ros_gz_interfaces gp2_interfaces)

# TODO (R7): needs checkpoint_frames_main.cpp and checkpoint_frames_node.cpp.
# add_executable(checkpoint_frames_exe src/checkpoint_frames_main.cpp
#   src/checkpoint_frames_node.cpp)
# ament_target_dependencies(checkpoint_frames_exe rclcpp geometry_msgs tf2_ros)

# TODO (R3 to R7): uncomment, and delete the executables you have not written yet.
# install(TARGETS patrol_status_exe operator_exe controller_exe mission_exe
#   checkpoint_frames_exe
#   DESTINATION lib/${PROJECT_NAME})

# R2: your YAML files go in config/. R9: your launch file goes in launch/.
install(DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME})

ament_package()
