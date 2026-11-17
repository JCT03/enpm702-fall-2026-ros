#pragma once
#include <cmath>
#include <geometry_msgs/msg/quaternion.hpp>
#include <numbers>

namespace gp2_patrol {

/**
 * @brief Heading (yaw) in radians of a quaternion, counterclockwise from +x.
 * @param orientation The orientation, for example `odometry.pose.pose.orientation`.
 * @return The yaw, in (-pi, pi].
 */
inline double yaw_from_quaternion(const geometry_msgs::msg::Quaternion &orientation) {
    const double siny_cosp{2.0 * (orientation.w * orientation.z +
                                  orientation.x * orientation.y)};
    const double cosy_cosp{1.0 - 2.0 * (orientation.y * orientation.y +
                                        orientation.z * orientation.z)};
    return std::atan2(siny_cosp, cosy_cosp);
}

/**
 * @brief Quaternion of a rotation about the z axis, with only z and w set.
 * @param yaw The heading in radians.
 * @return A quaternion with x = 0, y = 0, z = sin(yaw / 2) and w = cos(yaw / 2).
 */
inline geometry_msgs::msg::Quaternion quaternion_from_yaw(double yaw) {
    geometry_msgs::msg::Quaternion orientation{};
    orientation.z = std::sin(yaw / 2.0);
    orientation.w = std::cos(yaw / 2.0);
    return orientation;
}

/**
 * @brief Straight-line distance between two points.
 * @param from_x x of the first point, in meters.
 * @param from_y y of the first point, in meters.
 * @param to_x x of the second point, in meters.
 * @param to_y y of the second point, in meters.
 * @return The distance in meters, never negative.
 */
inline double distance_between(double from_x, double from_y, double to_x, double to_y) {
    return std::hypot(to_x - from_x, to_y - from_y);
}

/**
 * @brief Direction from one point to another, counterclockwise from +x.
 * @param from_x x of the starting point, in meters.
 * @param from_y y of the starting point, in meters.
 * @param to_x x of the target point, in meters.
 * @param to_y y of the target point, in meters.
 * @return The bearing in radians, in (-pi, pi].
 */
inline double bearing_between(double from_x, double from_y, double to_x, double to_y) {
    return std::atan2(to_y - from_y, to_x - from_x);
}

/**
 * @brief Wrap an angle to the range (-pi, pi].
 * @param angle An angle in radians, of any size.
 * @return The same direction as an angle greater than -pi and at most pi.
 */
inline double wrap_angle(double angle) {
    constexpr double two_pi{2.0 * std::numbers::pi};
    double wrapped{std::fmod(angle + std::numbers::pi, two_pi)};
    if (wrapped <= 0.0) {
        wrapped += two_pi;
    }
    return wrapped - std::numbers::pi;
}

/**
 * @brief Signed angle to turn from one heading to another, the short way.
 * @param target The heading to reach, in radians.
 * @param current The heading now, in radians.
 * @return target - current, wrapped to (-pi, pi]. Positive means turn counterclockwise.
 */
inline double angle_difference(double target, double current) {
    return wrap_angle(target - current);
}

} // namespace gp2_patrol
