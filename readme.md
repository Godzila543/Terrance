# Cheatsheet
## Useful Commands
+ `pip install inputs` install the controller input library
+ `colcon build --cmake-clean-cache` build all packages, and clean the cache to allow building on a new system
+ `colcon build --packages-select py_publisher` build the python package
+ `ros2 run py_publisher gamepad` run the gamepad input node
+ `python ./scripts/gamepad_server.py` run the gamepad server

+ `ssh seds@seds-desktop.local` ssh into the pi
+ `sudo -s -E` go sudo without losing context
+ `source ./install/setup.bash` source ros2 stuff

## Useful Links
+ [Python Pubilsher](https://docs.ros.org/en/iron/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Py-Publisher-And-Subscriber.html)
+ [ROS2 Iron Doc](https://docs.ros.org/en/iron/Installation.html)
