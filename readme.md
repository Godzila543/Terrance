# Gamepad steps for WSL (NOT WORKING)
Install usbipd-win
use `usbipd list` to find device
`usbipd bind --busid num-num`
`usbipd attach --wsl --busid <busid>`
