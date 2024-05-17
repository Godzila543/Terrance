# Python
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import socket
import json

class GamepadNode(Node):
    def __init__(self):
        super().__init__('gamepad_node')
        self.publisher_ = self.create_publisher(String, 'gamepad', 10)
        timer_period = 0.1  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)

        # Create a TCP/IP socket
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # Connect the socket to the port where the server is listening
        server_address = ('localhost', 12345)

        # Try connecting till the server is up
        while True:
            try:
                self.sock.connect(server_address)
                break
            except ConnectionRefusedError:
                self.get_logger().info("Connection refused, retrying in 1 second")
                rclpy.spin_once(self, timeout_sec=1)

    def timer_callback(self):
        # Receive data
        data = self.sock.recv(1024)
        input_data = json.loads(data.decode('utf-8'))
        msg = String()
        msg.data = f"Axes: {input_data['axes']}, Buttons: {input_data['buttons']}"
        self.publisher_.publish(msg)
        # log
        self.get_logger().info(f"Publishing: {msg.data}")

def main(args=None):
    rclpy.init(args=args)

    gamepad_node = GamepadNode()

    rclpy.spin(gamepad_node)

    gamepad_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()