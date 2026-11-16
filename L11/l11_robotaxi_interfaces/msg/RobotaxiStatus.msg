# The robotaxi's modes: each constant has a fixed value.
uint8 MODE_IDLE=0
uint8 MODE_EN_ROUTE=1
uint8 MODE_PICKING_UP=2
uint8 MODE_CHARGING=3

# When the status was taken, and the frame the position is in.
std_msgs/Header header

string robotaxi_name          # which robotaxi of the fleet
uint8 mode                    # one of the MODE_ constants above
geometry_msgs/Point position  # where the robotaxi is, in m
float32 battery               # battery level, in percent
