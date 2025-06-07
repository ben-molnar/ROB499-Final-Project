-----------------------
Contributions
-----------------------

Chatgpt for ros debugging

-----------------------
Run 2 terminals with:
-----------------------

cd ros2_ws/ 

colcon build

source install/setup.bash

-----------------------
Run the following launch file in a terminal:
(Launches camera.py and velocity.py)
-----------------------

ros2 launch final_project rob_arm_launch.py

-----------------------
to test if the service call works, in the other terminal, run
-----------------------

ros2 service call /toggle_operation std_srvs/srv/SetBool "{data: true}"

-----------------------
run the same service call but replace true with false to pause the nodes.
-----------------------
to test if there is a connection with the arduino, run:
-----------------------

ros2 topic pub /color_detected std_msgs/msg/String "data: 'red'"

-----------------------
To get camera.py to detect the color of objects, run
-----------------------

ros2 service call /capture_image std_srvs/srv/Trigger "{}"

-----------------------
run this service call after running /toggle_operation to test if camera.py runs if /toggle_operation was set to true and doesn't run if /toggle_operation was set to false.
