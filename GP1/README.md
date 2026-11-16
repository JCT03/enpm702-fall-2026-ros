# GP1 starter: Patrol and Inspect

This folder is the starter for GP1. The assignment page (Read the Docs,
Assignments, GP1) says what to build. This file says what is already here
and where your team starts.

## What is provided

```text
GP1/
├── README.md                     this file
├── gp1_interfaces/               messages only (CMake)
│   ├── CMakeLists.txt            complete, with TODO marks
│   ├── package.xml               complete, with TODO marks
│   └── msg/.gitkeep              your three message files go in msg/
└── gp1_patrol/                   C++ nodes (rclcpp)
    ├── CMakeLists.txt            complete, with TODO marks
    ├── package.xml               complete, with TODO marks
    ├── launch/.gitkeep           your two launch files go in launch/
    └── include/gp1_patrol/
        ├── checkpoints.hpp       the checkpoint table
        └── geometry.hpp          small math helpers
```

There are no node sources, no `main` files, no messages and no launch
files. Your team writes them.

### checkpoints.hpp

It declares, in the namespace `gp1_patrol`:

* `Checkpoint`: a struct with `x`, `y` (meters), `kind` (an `Arrival::KIND_`
  constant) and `scan_range_m` (the range the stand-in scan returns there).
* `kCheckpoints`: the four checkpoints, in the order the robot visits them.
* `kNearDistanceM`: 0.3 m, how close the robot must be for the stand-in
  scan to return the checkpoint's range.
* `kFarRangeM`: 4.0 m, the range everywhere else.

The header includes `gp1_interfaces/msg/arrival.hpp` for `KIND_ROOM` and
`KIND_DOOR`. It compiles only after your `Arrival.msg` (R1) builds, with
those two constants as `uint8`.

### geometry.hpp

Header-only helpers in the namespace `gp1_patrol`. Angles are in radians.

* `yaw_from_quaternion(orientation)`: the heading of a
  `geometry_msgs::msg::Quaternion`.
* `quaternion_from_yaw(yaw)`: a quaternion with only `z` and `w` set.
* `distance_between(from_x, from_y, to_x, to_y)`: the distance between two points.
* `bearing_between(from_x, from_y, to_x, to_y)`: the direction from the first
  point to the second, counterclockwise from +x.
* `wrap_angle(angle)`: the same direction as an angle in (-pi, pi].
* `angle_difference(target, current)`: how far to turn from `current` to
  `target`, the short way, in (-pi, pi]. Positive means counterclockwise.

Each function has a Doxygen comment. Use them: do not write this math again.

## Build

From your workspace root (the folder that holds `src/`):

```bash
source /opt/ros/jazzy/setup.bash
colcon build --packages-up-to gp1_patrol
source install/setup.bash
```

As delivered, both packages build and nothing runs: there are no messages
and no executables yet. `gp1_patrol` already depends on `gp1_interfaces` in
`package.xml`, so colcon builds the interfaces first.

## TODOs, in order

Search for `TODO` in the two `CMakeLists.txt` and the two `package.xml`.

1. **Maintainers (both `package.xml`).** Replace the three placeholder
   `<maintainer>` lines with each team member's name and email. Do it on
   day one, so the build never ships the placeholders.
2. **R1: messages (`gp1_interfaces`).** Write `Arrival.msg`,
   `InspectionReport.msg` and `StopCommand.msg` in `msg/`. In
   `gp1_interfaces/CMakeLists.txt`, uncomment the line of each message in
   `GP1_MESSAGE_FILES` as you add its file. Build, then check each one with
   `ros2 interface show gp1_interfaces/msg/Arrival`.
3. **Use the interfaces (`gp1_patrol/CMakeLists.txt`).** Once R1 builds,
   uncomment `find_package(gp1_interfaces REQUIRED)`.
4. **R2: stand-in robot.** Write `stand_in_robot_node` and
   `stand_in_robot_main.cpp`. Uncomment `stand_in_robot_exe`.
5. **R3 and R4: log and navigation.** Write `patrol_log_node` and
   `navigation_node`, each as `.hpp` and `.cpp`.
6. **R5: two executables.** Write `patrol_single_main.cpp` and
   `patrol_main.cpp`. Uncomment `patrol_single_exe` and `patrol_exe`.
7. **R6: mission and operator.** Write `mission_node`, `operator_node` and
   their `main` files. Uncomment `mission_exe` and `operator_exe`.
8. **Install list.** Uncomment the `install(TARGETS ...)` block in
   `gp1_patrol/CMakeLists.txt` and delete the names of executables you have
   not written yet. Without it, `ros2 run` cannot find your executables.
9. **R7: launch files.** Write `robots_launch.py` and `patrol_launch.py` in
   `launch/`. The `install(DIRECTORY launch ...)` line is already active.
10. **R8: documentation and demo.** Write `run_demo.sh` at the workspace
    root, your own `README.md` and `CONTRIBUTIONS.md`, and keep the R5
    evidence logs in `evidence/`.

Build after each step. Each step should build with no warnings.
