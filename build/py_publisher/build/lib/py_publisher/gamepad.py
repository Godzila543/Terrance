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
        self.buffer = ""
        self.server_address = ('192.168.192.1', 54535)
        self.get_logger().info('Connecting to gamepad server (check server and address if no connection)')
        self.connect_to_server()

    def connect_to_server(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        while True:
            try:
                self.sock.connect(self.server_address, timeout=1)
                self.get_logger().info('Connected to gamepad server')
                break
            except ConnectionRefusedError:
                self.get_logger().warn("Connection refused, retrying in 1 second")
                rclpy.spin_once(self, timeout_sec=1)

    def timer_callback(self):
        # Receive data
        try:
            data = self.sock.recv(1024)
            if not data:  # connection closed
                self.get_logger().error("Connection closed, reconnecting")
                self.sock.close()
                self.connect_to_server()
            else:
                self.buffer += data.decode("utf-8")
                while "\n" in self.buffer:
                    line, self.buffer = self.buffer.split("\n", 1)
                    # Decode and print the data
                    gamepad_data = json.loads(line)
                    msg = String()
                    msg.data = f"Axes: {gamepad_data['axes']}, Buttons: {gamepad_data['buttons']}"
                    self.publisher_.publish(msg)
        except socket.error as e:
            self.get_logger().error(f"Socket error: {e}, reconnecting")
            self.sock.close()
            self.connect_to_server()

def main(args=None):
    rclpy.init(args=args)

    gamepad_node = GamepadNode()

    rclpy.spin(gamepad_node)

    gamepad_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()