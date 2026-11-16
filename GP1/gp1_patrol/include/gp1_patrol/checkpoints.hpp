#pragma once
#include <array>
#include <cstdint>
#include <gp1_interfaces/msg/arrival.hpp>

namespace gp1_patrol {

// One checkpoint: position in meters in the robot's odometry frame, kind (an
// Arrival::KIND_ constant) and the range the stand-in scan returns there.
struct Checkpoint {
    double x;
    double y;
    std::uint8_t kind;
    float scan_range_m;
};

// Both robots visit these four checkpoints, in this order. The stand-in scan
// returns the range of the checkpoint within kNearDistanceM of it, else kFarRangeM.
inline constexpr std::array<Checkpoint, 4> kCheckpoints{{
    {2.0, 0.0, gp1_interfaces::msg::Arrival::KIND_ROOM, 4.0F},
    {2.0, 2.0, gp1_interfaces::msg::Arrival::KIND_ROOM, 0.6F},
    {0.0, 2.0, gp1_interfaces::msg::Arrival::KIND_DOOR, 0.6F},
    {0.0, 4.0, gp1_interfaces::msg::Arrival::KIND_DOOR, 4.0F},
}};

inline constexpr double kNearDistanceM{0.3};
inline constexpr float kFarRangeM{4.0F};

} // namespace gp1_patrol
