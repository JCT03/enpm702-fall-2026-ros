# gp2_bringup

Starts Gazebo Harmonic with the Husarion ROSbot in the GP2 patrol world.
It starts, in one launch file:

- the Gazebo simulation (window or server only) with the world you choose,
- the ROSbot spawned in it, with its controllers, EKF, lidar and `/clock` bridge
  (these come from the Husarion packages in the folder `rosbot_sim/`, which you do not change),
- a fixed camera high above the building, bridged to ROS 2,
- a front-facing Gazebo logical camera on the ROSbot, bridged to ROS 2 (see "The logical
  camera" below).

## Build

`gp2_bringup` is in the course repo, in the folder `rosbot_sim/` with the Husarion packages. With the
course repo cloned at `~/ros2_ws/src/enpm702-fall-2026-ros`:

```bash
cd ~/ros2_ws
source /opt/ros/jazzy/setup.bash
rosdep install --from-paths src --ignore-src -y
colcon build --symlink-install
source install/setup.bash
```

## Launch

```bash
ros2 launch gp2_bringup gp2_sim.launch.py
```

| Argument | Default | Meaning |
|---|---|---|
| `gui` | `true` | `true` opens the Gazebo window. `false` runs the server only (no window), for a remote or headless PC. |
| `world` | `patrol` | `patrol`, `patrol_doors_swapped`, `empty`, or the path of an `.sdf` file. |
| `rviz` | `false` | `true` opens RViz with the ROSbot's configuration. |
| `x`, `y`, `yaw` | `0.0` | Start pose of the robot in the world (meters, radians). |
| `logical_camera` | `true` | `false` leaves out the logical camera. |

Examples:

```bash
ros2 launch gp2_bringup gp2_sim.launch.py world:=patrol_doors_swapped
ros2 launch gp2_bringup gp2_sim.launch.py gui:=false rviz:=true   # server only, RViz window
```

Gazebo needs about 40 s to start the first time. Wait until `ros2 topic list` shows
`/odometry/filtered`.

## The worlds

`patrol.sdf` is one floor, 20 m by 10 m, with walls 1 m high (so the fixed camera sees
inside). The robot starts at the origin facing east, and the origin of the `odom` frame is
that start pose, so the world frame and `odom` are the same at the start. Coordinates are in
meters; x points east, y points north.

- Hall: x from -3 to 17, y from -3 to 2 (5 m wide). Two rooms lie north of it (y from 2 to 7,
  split at x = 7), reached through two doorways, each 3 m wide, in the wall y = 2.
- Door 3 at x = 12 is closed: a red panel fills the doorway. Door 4 at x = 3 is open.
- A crate (1.2 m by 0.8 m) stands at (9.5, -2.4), against the south wall.
- Blue discs on the floor mark the four checkpoints: (5.0, -0.5), (9.5, -1.4), (12.0, 0.4)
  and (3.0, 0.4). The start (0, 0) and every checkpoint are at least 1.5 m from every wall.
- Objects for the logical camera (each is a Gazebo model with its own name; the number is the
  model's origin):

  | Model | Where | Seen from |
  |---|---|---|
  | `fire_extinguisher` | (7.6, 1.3, 0.25) | checkpoint 1 |
  | `crate` | (9.5, -2.4, 0.4) | checkpoint 2 |
  | `person` | (11.6, 1.45, 0.65) | checkpoint 3 |
  | `spill` | (3.6, 1.3, 0.006) | checkpoint 4 |

`patrol_doors_swapped.sdf` is the same building with door 3 open and door 4 closed, with no
`fire_extinguisher` and no `person`. `empty.sdf` is a flat floor with the fixed camera.
All three worlds hold the plugin that runs the logical camera.

## The logical camera

A Gazebo logical camera does not make a picture. It lists the models that are inside its view
volume and gives each model's name and pose. The ROSbot gets one, facing forward.

| | |
|---|---|
| Topic | `/logical_camera` (10 Hz) |
| Type | `ros_gz_interfaces/msg/LogicalCameraImage` |
| Frame | `logical_camera_link`, 0.12 m ahead of and 0.20 m above `base_link` (x forward, y left, z up) |
| View volume | horizontal field of view 2.0 rad (115 degrees), aspect ratio 1 (the same angle up and down), distance from 0.3 m to 3.5 m along the camera's x axis |

```bash
ros2 topic echo --once /logical_camera
```

The message has a `header` (frame `logical_camera_link`), the camera's own `pose` in the
Gazebo world, and a list `model`. Each entry has the `name` of the model and its `pose` **in
the camera frame**. To get a position in `odom`, transform it with tf2. Know these points:

- The camera lists every model whose origin is inside the view volume, not only the objects:
  walls, doors, the blue checkpoint discs and the fixed camera appear too, so you filter by name.
  The floor's origin is the point (0, 0, 0), so `floor` also appears when the robot looks at it
  from less than 3.5 m.
- Nothing hides anything: the camera sees through walls and behind the crate.
- A model counts when its **origin** is inside the volume (a test: a crate whose center was
  3.58 m ahead was not listed, although its front face was 3.18 m ahead).
- The ROSbot's `odom` frame is 5 % short, so a position in `odom` is off by about 5 % of the
  distance driven (see "Topics and frames"). The model poses in the camera frame are exact.

How it is attached, without a change to the Husarion packages: `models/logical_camera_rig.sdf` is a
small model with the sensor and a `DetachableJoint` plugin. The launch file spawns it at the
robot's start pose, and the plugin joins its link to the robot's `base_link` with a fixed
joint. The rig has no collision shape and a mass of 0.05 kg. It also holds a yellow disc on the
floor under the robot (visual only), so that the robot shows in the video. The launch file
publishes the static transform `base_link` to `logical_camera_link` and bridges the topic with
`ros_gz_bridge`.

## Drive the robot from a terminal

The ROSbot listens to `cmd_vel` of type `geometry_msgs/msg/TwistStamped` (not `Twist`).

```bash
# 0.2 m/s forward, until you press Ctrl-C
ros2 topic pub -r 10 /cmd_vel geometry_msgs/msg/TwistStamped \
  "{twist: {linear: {x: 0.2}}}"

# turn on the spot, 0.5 rad/s
ros2 topic pub -r 10 /cmd_vel geometry_msgs/msg/TwistStamped \
  "{twist: {angular: {z: 0.5}}}"
```

With the keyboard (the `stamped` parameter makes the node publish `TwistStamped`):

```bash
ros2 run teleop_twist_keyboard teleop_twist_keyboard --ros-args -p stamped:=true
```

The robot stops by itself when no `cmd_vel` arrives for 0.5 s (the controller's `cmd_vel_timeout`).

## Topics and frames

| Topic | Type | Meaning |
|---|---|---|
| `/cmd_vel` | `geometry_msgs/msg/TwistStamped` | Velocity command (input). |
| `/odometry/filtered` | `nav_msgs/msg/Odometry` | Pose in `odom` (wheels and IMU, through an EKF). |
| `/scan` | `sensor_msgs/msg/LaserScan` | Lidar, frame `laser`, 3000 beams, -pi to pi, 0.05 to 30 m. |
| `/scan_filtered` | `sensor_msgs/msg/LaserScan` | The same scan without the beams that hit the robot itself. |
| `/tf`, `/tf_static` | `tf2_msgs/msg/TFMessage` | Frames. |
| `/clock` | `rosgraph_msgs/msg/Clock` | Simulation time. Nodes you write use `use_sim_time:=true`. |
| `/patrol_cam/image`, `/patrol_cam/camera_info` | `sensor_msgs/msg/Image`, `CameraInfo` | The fixed camera (1920 by 1080, RGB). |
| `/logical_camera` | `ros_gz_interfaces/msg/LogicalCameraImage` | The logical camera, frame `logical_camera_link`. |
| `/joint_states`, `/imu/data`, `/oak/...` | | Other sensors of the ROSbot. |

Frames: `odom` is the parent of `base_link`. `laser` is fixed to the robot, 0.02 m ahead of
and 0.131 m above `base_link`. `base_link` has x forward, y left. **The lidar frame `laser` is turned by 180 degrees
about z**, so the direction straight ahead of the robot is at angle +pi (and -pi) in the
scan, not 0. Check with `ros2 run tf2_ros tf2_echo base_link laser`.

`odom` is not exact. In `patrol.sdf` the pose in `odom` falls short of the true travel by
about 5 %: after 6 m of driving, `odom` said x = 5.96 while Gazebo's true position was
6.28. The cause is in `rosbot_controller/config/rosbot/controllers.yaml`:
`left_wheel_radius_multiplier` and `right_wheel_radius_multiplier` are 0.95 ("Based on real
measurements"), and the simulated wheels have the radius 0.0425 m that the controller assumes, so the multiplier is only an error here. You do not change that file.

## System packages to install

ROS 2 Jazzy, Gazebo Harmonic and `ros-jazzy-ros-gz` (the course setup). The `rosdep install`
command above installs the rest: `controller-manager`, `diff-drive-controller`,
`imu-sensor-broadcaster`, `joint-state-broadcaster`, `position-controllers`,
`ros2controlcli`, `gz-ros2-control`, `robot-localization`, `laser-filters`,
`joint-state-publisher`, `depthai-descriptions`, `nav2-common` and `launch-pytest`, all
`ros-jazzy-<name>`. `rosbot_sim/README.md` says what was removed from the Husarion packages.
