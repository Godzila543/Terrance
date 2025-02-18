#! /bin/python3

import socket
import random
import time

UDP_IP = "192.168.1.101"  # IP address of the Raspberry Pi
UDP_PORT = 4210
MESSAGE = "Your command or data"

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Send a UDP packet to the ESP32
sock.sendto(MESSAGE.encode(), (UDP_IP, UDP_PORT))
i = 0
while True:
    sock.sendto((MESSAGE + str(i)).encode(), (UDP_IP, UDP_PORT))
    i += 1
    if i > 100:
        break

    time.sleep(0.1)
