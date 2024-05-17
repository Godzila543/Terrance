## Useful Links
[Python Pubilsher](https://docs.ros.org/en/iron/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Py-Publisher-And-Subscriber.html)
[ROS2 Iron Doc](https://docs.ros.org/en/iron/Installation.html)

### Gamepad steps for WSL (NOT WORKING)
Install usbipd-win
use `usbipd list` to find device
`usbipd bind --busid num-num`
`usbipd attach --wsl --busid <busid>`
