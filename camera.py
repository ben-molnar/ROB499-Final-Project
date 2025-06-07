#!/usr/bin/env python3


#Detects the color of a block
#
#camera.py
#
#Ben Molnar
#
#Takes in images of a block and determiens the color of the block

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2
from std_msgs.msg import String
from std_srvs.srv import SetBool, Trigger

import requests
import numpy as np

class Camera(Node):
    def __init__(self):
        super().__init__('camera')
        self.bridge = CvBridge()

        #create the publisher and services
        self.pub = self.create_publisher(String, "/color_detected", 10)
        self.srv = self.create_service(SetBool, 'toggle_operation', self.toggle_operation)

        self.srv = self.create_service(Trigger, 'capture_image', self.capture)

        # url to access the latest image from the camera
        # change to correct ip given after uploading code to camera
        self.camera_url = "http://10.2.79.252/capture?_cb=1748819543203"

        #node starts off paused
        self.operating = False

        self.get_logger().info("Camera node initialized. Start node to begin operation")
    
    # changes the state of self.operating
    def toggle_operation(self, req, resp):
        self.operating = req.data

        if self.operating:
            self.get_logger().info("Camera node is now running.")
        else:
            self.get_logger().info("Camera node is now paused.")

        resp.success = True
        resp.message = f"Camera node sate changed"
        return resp

    #save the latest image
    def capture(self, req, resp):
        try:
            response = requests.get(self.camera_url)
            image = np.asarray(bytearray(response.content))
            img = cv2.imdecode(image, cv2.IMREAD_COLOR)

            filename = "latest_image.jpg"
            cv2.imwrite(filename, img)
            self.get_logger().info(f"Image saved as {filename}")

            resp.success = True

            self.process_image(img)
        
        except Exception as e:
            resp.success = False
            self.get_logger().info(f"Error capturing image: {e}")
        
        return resp

    #publish detected color so velocity will send info to the arduino
    def process_image(self, image):
        if not self.operating:
            return

        color = self.detect_color(image)

        color_msg = String()
        color_msg.data = color
        self.pub.publish(color_msg)

        self.get_logger().info(f"Detected color: {color}")
    
    def detect_color(self, image):
        height, width, _ = image.shape

        #region of interest (relative area of the picture that contains the block)
        roi_size = 50

        # finds the center of the image (assuming the block is located in the center)
        x_start = (width // 2) - (roi_size // 2)
        y_start = (height // 2) - (roi_size // 2)

        #keep the region of interest and convert to HSV
        roi = image[y_start:y_start + roi_size, x_start:x_start + roi_size]
        hsv = cv2.cvtColor(roi, cv2.COLOR_BGR2HSV)

        #checks if the color of the region of interest is red, green, blue, or unknown
        if self.in_threshold(hsv, (0, 60, 60), (10, 255, 255)):
            return "red"

        if self.in_threshold(hsv, (35, 60, 60), (85, 255, 255)):
            return "green"
        
        if self.in_threshold(hsv, (100, 90, 0), (140, 255, 255)):
            return "blue"
        
        return "unknown"
    
    # takes in the hsv, and lower/upper color bounds
    def in_threshold(self, hsv, lower, upper):

        # create a binary mask showing which pixels match the range
        mask = cv2.inRange(hsv, lower, upper)

        #checks if the number of pixels match the color range 
        return cv2.countNonZero(mask) > 50

def main(args=None):
    rclpy.init(args=args)
    node = Camera()
    rclpy.spin(node)
    rclpy.shutdown()
    
if __name__ == '__main__':
    main()
