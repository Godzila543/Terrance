import rclpy
from rclpy.node import Node
from inputs import get_gamepad

class GamepadNode(Node):

    def __init__(self):
        super().__init__('gamepad_node')
        self.get_logger().info('Gamepad node started')
        self.create_timer(0.1, self.gamepad_callback) # Check gamepad input every 0.1 seconds

    def gamepad_callback(self):
        events = get_gamepad()
        for event in events:
            # Check for specific events
            if event.code == 'ABS_Y':
                self.get_logger().info(f'Left Stick Y: {event.state}')
            elif event.code == 'BTN_SOUTH':
                self.get_logger().info('A Button Pressed')
            # ... (Add more event handling as needed)

def main(args=None):
    rclpy.init(args=args)
    gamepad_node = GamepadNode()
    rclpy.spin(gamepad_node)
    gamepad_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
