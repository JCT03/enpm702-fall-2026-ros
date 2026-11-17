#pragma once

namespace l11_robotaxi::color {

// Terminal colors for the callbacks' log lines, the same colors as the
// slides' figures. Each is an ANSI escape code: "\033[38;2;R;G;Bm" sets the
// text color (red, green, blue, 0 to 255), and "\033[0m" goes back to the
// terminal's own color. GNOME Terminal and the VS Code terminal read them.
inline constexpr const char *sensor_callback{"\033[38;2;27;122;58m"};    // green
inline constexpr const char *health_callback{"\033[38;2;106;61;154m"};   // purple
inline constexpr const char *command_callback{"\033[38;2;179;89;0m"};    // orange
inline constexpr const char *watchdog_callback{"\033[38;2;21;101;192m"};  // blue
inline constexpr const char *sensors_node{"\033[38;2;31;95;168m"};       // blue
inline constexpr const char *health_node{"\033[38;2;163;36;107m"};       // magenta
// The four timers of callback_groups_node: one color per callback.
inline constexpr const char *timer1{"\033[38;2;21;101;192m"};   // blue
inline constexpr const char *timer2{"\033[38;2;27;122;58m"};    // green
inline constexpr const char *timer3{"\033[38;2;106;61;154m"};   // purple
inline constexpr const char *timer4{"\033[38;2;179;89;0m"};     // orange
inline constexpr const char *reset{"\033[0m"};

} // namespace l11_robotaxi::color
