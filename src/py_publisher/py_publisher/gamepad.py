# Python
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import socket
import json
import queue
import threading
from inputs import devices

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

print("Welcome to the super cool and awesome gamepad server!")
print("Press Ctrl+C to shut down the server.")
print("Please move the gamepad if the server is not responding.\n")

# Initialize Gamepad
if not devices.gamepads:
    print(
        "\033[31m" + "No gamepad found. Please connect a gamepad." + "\033[0m"
    )
    exit(1)

gamepad = devices.gamepads[0]
gamepad_events = queue.Queue()

# Flag to signal the read_gamepad thread to stop
stop_reading = threading.Event()


# Function to read gamepad events and put them in the queue
def read_gamepad():
    while not stop_reading.is_set():
        events = gamepad.read()
        gamepad_events.put(events)


# Start a separate thread to read gamepad events
gamepad_thread = threading.Thread(target=read_gamepad)
gamepad_thread.start()

class GamepadNode(Node):
    def __init__(self):
        super().__init__('gamepad_node')
        self.controller = Controller()
        self.publisher_ = self.create_publisher(String, 'gamepad', 10)


        timer_period = 0.05  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)

    def timer_callback(self):
        while (not gamepad_events.empty()):
            events = gamepad_events.get()
            data = {
                "axes": {
                    event.code: event.state
                    for event in events
                    if event.ev_type == "Absolute"
                },
                "buttons": {
                    event.code: event.state
                    for event in events
                    if event.ev_type == "Key"
                },
            }
            # Decode and print the data
            self.controller.update(data)
            msg = String()
            msg.data = json.dumps(self.controller.state)
            self.publisher_.publish(msg)

def main(args=None):
    rclpy.init(args=args)

    gamepad_node = GamepadNode()

    rclpy.spin(gamepad_node)

    gamepad_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()