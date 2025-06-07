#!/usr/bin/env python3


# Launch file for camera.py and velocity.py
#
#rob_arm_launch.py
#
#Ben Molnar
#
#

import os

from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package="final_project",
            executable="camera",
            name="camera",
        ),
        Node(
            package="final_project",
            executable="velocity",
            name="velocity",
        ),
    ])
