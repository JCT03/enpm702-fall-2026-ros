cmake_minimum_required(VERSION 3.8)
project(gp1_patrol)

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
# TODO (R1): uncomment once gp1_interfaces builds with your messages.
# find_package(gp1_interfaces REQUIRED)

include_directories(include)

# TODO (R2): needs stand_in_robot_main.cpp and stand_in_robot_node.cpp.
# add_executable(stand_in_robot_exe src/stand_in_robot_main.cpp
#   src/stand_in_robot_node.cpp)
# ament_target_dependencies(stand_in_robot_exe rclcpp geometry_msgs nav_msgs
#   sensor_msgs gp1_interfaces)

# TODO (R5): needs patrol_single_main.cpp, navigation_node.cpp, patrol_log_node.cpp.
# add_executable(patrol_single_exe src/patrol_single_main.cpp
#   src/navigation_node.cpp src/patrol_log_node.cpp)
# ament_target_dependencies(patrol_single_exe rclcpp geometry_msgs nav_msgs
#   gp1_interfaces)

# TODO (R5): needs patrol_main.cpp, navigation_node.cpp, patrol_log_node.cpp.
# add_executable(patrol_exe src/patrol_main.cpp
#   src/navigation_node.cpp src/patrol_log_node.cpp)
# ament_target_dependencies(patrol_exe rclcpp geometry_msgs nav_msgs gp1_interfaces)

# TODO (R6): needs mission_main.cpp and mission_node.cpp.
# add_executable(mission_exe src/mission_main.cpp src/mission_node.cpp)
# ament_target_dependencies(mission_exe rclcpp sensor_msgs gp1_interfaces)

# TODO (R6): needs operator_main.cpp and operator_node.cpp.
# add_executable(operator_exe src/operator_main.cpp src/operator_node.cpp)
# ament_target_dependencies(operator_exe rclcpp gp1_interfaces)

# TODO (R2, R5, R6): uncomment, and delete the executables you have not written yet.
# install(TARGETS stand_in_robot_exe patrol_single_exe patrol_exe mission_exe
#   operator_exe
#   DESTINATION lib/${PROJECT_NAME})

# R7: your two launch files go in launch/.
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})

ament_package()
