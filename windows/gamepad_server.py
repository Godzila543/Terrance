# AUTHORS - Github Copilot, Colin Brown
# Python
import pygame
import socket
import json

# Initialize Pygame
pygame.init()

# Initialize Joystick
joystick = pygame.joystick.Joystick(0)
joystick.init()

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to the port
server_address = ('localhost', 12345)
sock.bind(server_address)

# Listen for incoming connections
sock.listen(1)

while True:
    # Wait for a connection
    connection, client_address = sock.accept()
    try:
        # Read joystick input
        pygame.event.pump()
        data = {
            'axes': [joystick.get_axis(i) for i in range(joystick.get_numaxes())],
            'buttons': [joystick.get_button(i) for i in range(joystick.get_numbuttons())]
        }
        # Send data
        connection.sendall(json.dumps(data).encode('utf-8'))
        # log
        print(f"Sending: {data}")
    finally:
        # Clean up the connection
        connection.close()