#!/usr/bin/env python3


#Takes in a color and publishes a velocity command
#
#camera.py
#
#Ben Molnar
#
#

import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from std_srvs.srv import SetBool
import serial

class Velocity(Node):
    def __init__(self):
        super().__init__('velocity')

        self.ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)

        #create the subscriber and service
        self.sub = self.create_subscription(String, "/color_detected", self.handle_color, 10)

        # Node starts paused by default
        self.operating = False

        self.get_logger().info("Velocity node is now running.")
    
    # takes in the message from camera.py
    def handle_color(self, msg):

        # accesses the detected color
        color = msg.data
        self.get_logger().info(f"Received color: {color}")
        self.move_arm(color)
    
    # takes in the detected color and returns the velocity command unless and unknown color was detected
    def move_arm(self, color):
        velo_command = ""

        if color == "red":
            velo_command = "move_to_red_zone"
        elif color == "green":
            velo_command = "move_to_green_zone"
        elif color == "blue":
            velo_command = "move_to_blue_zone"
        else:
            self.get_logger().warn("Unknown color detected")
            return

        self.ser.write(velo_command.encode())
        
        self.get_logger().info(f"Sent to Arduino: {velo_command}")


def main(args=None):
    rclpy.init(args=args)
    node = Velocity()
    rclpy.spin(node)
    rclpy.shutdown()
    
if __name__ == '__main__':
    main()
