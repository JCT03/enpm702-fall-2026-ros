# GP2 starter: Patrol and Inspect in Gazebo

This folder is the starter for GP2. The assignment page (Read the Docs,
Assignments, GP2) says what to build. This file says what is already here
and where your team starts.

## What is provided

```text
GP2/
├── README.md                     this file
├── gp2_interfaces/               messages (CMake)
│   ├── CMakeLists.txt            complete, with TODO marks
│   ├── package.xml               complete, with TODO marks
│   └── msg/.gitkeep              your seven message files go in msg/
└── gp2_patrol/                   C++ nodes (rclcpp)
    ├── CMakeLists.txt            complete, with TODO marks
    ├── package.xml               complete, with TODO marks
    ├── config/.gitkeep           your YAML files go in config/
    ├── launch/.gitkeep           your launch file goes in launch/
    └── include/gp2_patrol/
        └── geometry.hpp          the math helpers of GP1
```

`geometry.hpp` is the GP1 header with the namespace changed to
`gp2_patrol`. Its six functions are documented in the header.

The simulation (`gp2_bringup`, the ROSbot and the two worlds) is in
`rosbot_sim/`, at the top of this repository. The ROSbot Simulation page
under Setup says how to install and build it.

There are no node sources, no `main` files, no interface files, no YAML
files and no launch file. Your team writes them, starting from your GP1
code.

## Build

From your workspace root (the folder that holds `src/`):

```bash
source /opt/ros/jazzy/setup.bash
colcon build --packages-up-to gp2_patrol
source install/setup.bash
```

As delivered, both packages build and nothing runs: there are no
interfaces and no executables yet. `gp2_patrol` already depends on
`gp2_interfaces` in `package.xml`, so colcon builds the interfaces first.

In Week 1 you test against the stand-in robot of GP1. Keep your GP1
packages in the workspace and run `ros2 run gp1_patrol stand_in_robot_exe`
with no namespace.

## TODOs, in order

Search for `TODO` in the two `CMakeLists.txt` and the two `package.xml`.

1. **Maintainers (both `package.xml`).** Replace the three placeholder
   `<maintainer>` lines with each team member's name and email.
2. **R1: interfaces (`gp2_interfaces`).** Write the seven message files.
   In `gp2_interfaces/CMakeLists.txt`, uncomment the line of each file in
   `GP2_INTERFACE_FILES` as you add it. Check each one with
   `ros2 interface show`, for example
   `ros2 interface show gp2_interfaces/msg/CheckpointGoal`.
3. **Use the interfaces (`gp2_patrol/CMakeLists.txt`).** Once R1 builds,
   uncomment `find_package(gp2_interfaces REQUIRED)`.
4. **R2: parameters.** Write `params_stand_in.yaml` and
   `params_gazebo.yaml` in `config/`.
5. **R3: patrol status and operator.** Write `patrol_status_node` and
   `operator_node` with their `main` files. Uncomment
   `patrol_status_exe` and `operator_exe`.
6. **R4 and R5: controller.** Write `controller_node` and its `main`
   file. Uncomment `controller_exe`.
7. **R6: mission.** Copy `patrol_log_node` from GP1, write
   `mission_node` and `mission_main.cpp`. Uncomment `mission_exe`.
8. **R7: checkpoint frames.** Write `checkpoint_frames_node` and its
   `main` file. Uncomment `checkpoint_frames_exe`.
9. **Install list.** Uncomment the `install(TARGETS ...)` block in
   `gp2_patrol/CMakeLists.txt` and delete the names of executables you
   have not written yet. Without it, `ros2 run` cannot find your
   executables.
10. **R9: launch file.** Write `gp2_launch.py` in `launch/`. The
    `install(DIRECTORY launch config ...)` line is already active.
11. **R11: documentation and demo.** Write `run_demo.sh` at the workspace
    root, your own `README.md` and `CONTRIBUTIONS.md`, and keep the logs
    in `evidence/`.

Build after each step. Each step should build with no warnings.
