# The oldest CMake that can build this package.
cmake_minimum_required(VERSION 3.8)
# The package's name: it must match <name> in package.xml.
project(l11_robotaxi)

# Compile as standard C++20, as in the C++ part of the course. Without these lines,
# g++ 13 uses its default, gnu++17: C++17 with GNU extensions.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # stop if the compiler has no C++20
set(CMAKE_CXX_EXTENSIONS OFF) # -std=c++20, not -std=gnu++20

# colcon build passes no build type. Debug adds -g, so breakpoints work in a debugger.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Turn on the compiler's warnings (GCC or Clang), as in the C++ part of the course:
# -Wall -Wextra: the common warnings; -pedantic-errors: code that is not standard C++
# is an error; -Wshadow: a variable that hides another one, such as a data member.
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -pedantic-errors -Wshadow)
endif()

# find dependencies: one line per package this package uses,
# the same packages as the <depend> lines of package.xml.
find_package(ament_cmake REQUIRED) # the build type of this package
find_package(rclcpp REQUIRED) # the ROS 2 C++ client library: nodes, publishers, timers
find_package(geometry_msgs REQUIRED) # the message types geometry_msgs/msg/Point and Twist
find_package(std_msgs REQUIRED) # the message type std_msgs/msg/Float64
find_package(l11_robotaxi_interfaces REQUIRED) # the message type RobotaxiStatus

# Lets #include "l11_robotaxi/..." find the headers in include/.
include_directories(include)

# The publisher: builds the executable robotaxi_exe from its main and its node class.
add_executable(robotaxi_exe src/robotaxi_main.cpp src/robotaxi_node.cpp)
ament_target_dependencies(robotaxi_exe rclcpp geometry_msgs)

# The subscriber: builds the executable dispatcher_exe the same way.
add_executable(dispatcher_exe src/dispatcher_main.cpp src/dispatcher_node.cpp)
ament_target_dependencies(dispatcher_exe rclcpp geometry_msgs)

# The camera and the controller, each in its own process.
add_executable(camera_exe src/camera_main.cpp src/camera_node.cpp)
ament_target_dependencies(camera_exe rclcpp std_msgs)
add_executable(controller_exe src/controller_main.cpp src/controller_node.cpp)
ament_target_dependencies(controller_exe rclcpp std_msgs geometry_msgs)

# The camera alone, with rclcpp::spin(node) written out as an executor.
add_executable(camera_executor_exe src/camera_executor_main.cpp src/camera_node.cpp)
ament_target_dependencies(camera_executor_exe rclcpp std_msgs)

# Two rclcpp::spin calls in a row: the controller never runs.
add_executable(spin_twice_exe src/spin_twice_main.cpp
  src/camera_node.cpp src/controller_node.cpp)
ament_target_dependencies(spin_twice_exe rclcpp std_msgs geometry_msgs)

# The camera and the controller in one single-threaded executor.
add_executable(single_executor_exe src/single_executor_main.cpp
  src/camera_node.cpp src/controller_node.cpp)
ament_target_dependencies(single_executor_exe rclcpp std_msgs geometry_msgs)

# A custom message: status_exe publishes RobotaxiStatus, fleet_monitor_exe receives it.
add_executable(status_exe src/status_main.cpp src/status_node.cpp)
ament_target_dependencies(status_exe rclcpp l11_robotaxi_interfaces)
add_executable(fleet_monitor_exe src/fleet_monitor_main.cpp src/fleet_monitor_node.cpp)
ament_target_dependencies(fleet_monitor_exe rclcpp l11_robotaxi_interfaces)

# A multi-threaded executor with three threads: one node with three timers,
# then two nodes with three timers each.
add_executable(mte_one_node_exe src/mte_one_node_main.cpp src/sensors_node.cpp)
ament_target_dependencies(mte_one_node_exe rclcpp)
add_executable(mte_two_nodes_exe src/mte_two_nodes_main.cpp
  src/sensors_node.cpp src/health_node.cpp)
ament_target_dependencies(mte_two_nodes_exe rclcpp)

# The callback group demos: one node, three group setups.
add_executable(two_mutex_exe
  src/two_mutex_main.cpp src/callback_groups_node.cpp)
ament_target_dependencies(two_mutex_exe rclcpp)
add_executable(two_reentrant_exe
  src/two_reentrant_main.cpp src/callback_groups_node.cpp)
ament_target_dependencies(two_reentrant_exe rclcpp)
add_executable(mutex_reentrant_exe
  src/mutex_reentrant_main.cpp src/callback_groups_node.cpp)
ament_target_dependencies(mutex_reentrant_exe rclcpp)

# Copies the executables to install/l11_robotaxi/lib/l11_robotaxi, where ros2 run and
# ros2 launch look for them.
install(TARGETS robotaxi_exe dispatcher_exe camera_exe controller_exe camera_executor_exe
  spin_twice_exe single_executor_exe
  status_exe fleet_monitor_exe mte_one_node_exe mte_two_nodes_exe two_mutex_exe two_reentrant_exe mutex_reentrant_exe
  DESTINATION lib/${PROJECT_NAME})

# Copies the launch folder to install/l11_robotaxi/share/l11_robotaxi, where ros2 launch
# looks for launch files.
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})

# Finishes the package (exports it so other packages can find it). It must be the last line.
ament_package()
