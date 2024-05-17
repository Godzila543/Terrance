# Cheatsheet
## Useful Commands
+ `pip install inputs` install the controller input library
+ `colcon build --cmake-clean-cache` build all packages, and clean the cache to allow building on a new system
+ `colcon build --packages-select py_publisher` build the python package
+ `ros2 run py_publisher gamepad` run the gamepad input node

## Useful Links
+ [Python Pubilsher](https://docs.ros.org/en/iron/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Py-Publisher-And-Subscriber.html)
+ [ROS2 Iron Doc](https://docs.ros.org/en/iron/Installation.html)

### Gamepad steps for WSL (NOT WORKING)
Install usbipd-win
use `usbipd list` to find device
`usbipd bind --busid num-num`
`usbipd attach --wsl --busid <busid>`
