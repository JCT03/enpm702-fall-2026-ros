cmake_minimum_required(VERSION 3.8)
project(gp2_interfaces)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# TODO (R1): write the interface files and uncomment each line below as you add
# its file. rosidl_generate_interfaces() fails with an empty list, so the call
# below runs only when at least one file is listed: the package builds empty
# until then.
set(GP2_INTERFACE_FILES
  # "msg/DetectedObject.msg"
  # "msg/InspectionReport.msg"
  # "msg/PatrolStatus.msg"
  # "msg/PatrolCommand.msg"
  # "msg/CheckpointGoal.msg"
  # "msg/CheckpointFeedback.msg"
  # "msg/CheckpointResult.msg"
)

# Generates C++ and Python code for each interface file.
if(GP2_INTERFACE_FILES)
  rosidl_generate_interfaces(${PROJECT_NAME}
    ${GP2_INTERFACE_FILES}
    DEPENDENCIES std_msgs geometry_msgs
  )
endif()

ament_package()
