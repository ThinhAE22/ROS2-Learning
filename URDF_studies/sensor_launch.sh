#!/bin/bash
#The launch for the gazebo not work on my version so this is an alternatives
# Launch Gazebo with the sensor world
gz sim sensor.sdf &

# Give it time to start
sleep 3

# Source ROS 2 workspace (adjust path if needed)
source ~/ros2_ws/install/setup.bash

# Run your lidar node
ros2 run lidar_node lidar_node
