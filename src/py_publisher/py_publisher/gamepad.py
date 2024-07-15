# Python
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import socket
import json

class Controller:
    def __init__(self):
        self.state = {
            "left_stick": {"x": 0, "y": 0},
            "right_stick": {"x": 0, "y": 0},
            "d_pad": {"x": 0, "y": 0},
            "triggers": {"left": 0, "right": 0},
            "buttons": {"a": 0, "b": 0, "x": 0, "y": 0,
                        "l1": 0, "r1": 0, "select": 0, "start": 0, "l_stick": 0, "r_stick": 0}
        }
        
    def update(self, data):
        state = self.state
        state["left_stick"]["x"] = data["axes"].get('ABS_X', state["left_stick"]["x"])
        state["left_stick"]["y"] = data["axes"].get('ABS_Y', state["left_stick"]["y"])
        state["right_stick"]["x"] = data["axes"].get('ABS_RX', state["right_stick"]["x"])
        state["right_stick"]["y"] = data["axes"].get('ABS_RY', state["right_stick"]["y"])
        state["d_pad"]["x"] = data["axes"].get('ABS_HAT0X', state["d_pad"]["x"])
        state["d_pad"]["y"] = data["axes"].get('ABS_HAT0Y', state["d_pad"]["y"])
        state["triggers"]["left"] = data["axes"].get('ABS_Z', state["triggers"]["left"])
        state["triggers"]["right"] = data["axes"].get('ABS_RZ', state["triggers"]["right"])
        state["buttons"]["y"] = data["buttons"].get('BTN_NORTH', state["buttons"]["y"])
        state["buttons"]["b"] = data["buttons"].get('BTN_EAST', state["buttons"]["b"])
        state["buttons"]["a"] = data["buttons"].get('BTN_SOUTH', state["buttons"]["a"])
        state["buttons"]["x"] = data["buttons"].get('BTN_WEST', state["buttons"]["x"])
        state["buttons"]["l1"] = data["buttons"].get('BTN_TL', state["buttons"]["l1"])
        state["buttons"]["r1"] = data["buttons"].get('BTN_TR', state["buttons"]["r1"])
        state["buttons"]["select"] = data["buttons"].get('BTN_SELECT', state["buttons"]["select"])
        state["buttons"]["start"] = data["buttons"].get('BTN_START', state["buttons"]["start"])
        state["buttons"]["l_stick"] = data["buttons"].get('BTN_THUMBL', state["buttons"]["l_stick"])
        state["buttons"]["r_stick"] = data["buttons"].get('BTN_THUMBR', state["buttons"]["r_stick"])


class GamepadNode(Node):
    def __init__(self):
        super().__init__('gamepad_node')
        self.controller = Controller()
        self.publisher_ = self.create_publisher(String, 'gamepad', 10)


        timer_period = 0.1  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)

        self.buffer = ""
        self.server_address = ('localhost', 54535)
        self.get_logger().info('Connecting to gamepad server (check server and address if no connection)')
        self.connect_to_server()

    def connect_to_server(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        while True:
            try:
                self.sock.connect(self.server_address)
                self.get_logger().info('Connected to gamepad server')
                break
            except ConnectionRefusedError:
                self.get_logger().warn("Connection refused, retrying in 1 second")
                rclpy.spin_once(self, timeout_sec=1)

    def timer_callback_old(self):
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
                    self.controller.update(gamepad_data)
                    msg = String()
                    msg.data = json.dumps(self.controller.state)
                    self.publisher_.publish(msg)
        except socket.error as e:
            self.get_logger().error(f"Socket error: {e}, reconnecting")
            self.sock.close()
            self.connect_to_server()

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
                    self.controller.update(gamepad_data)
                    msg = String()
                    msg.data = json.dumps(self.controller.state)
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