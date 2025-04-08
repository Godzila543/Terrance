"""
Rover Controller - Windows Script
Handles gamepad input, calculates motor RPMs, and sends commands to ESP32 via serial.
"""

import time
import json
import serial
import pygame

# Configuration
SERIAL_PORT = "COM3"  # Update to your ESP32 serial port
BAUD_RATE = 115200
MAX_RPM = 120  # Maximum RPM for the motors
UPDATE_RATE = 50  # Hz (updates per second)


class RoverController:
    def __init__(self):
        # Initialize pygame and joystick
        pygame.init()
        pygame.joystick.init()

        # Check for available gamepads
        if pygame.joystick.get_count() == 0:
            raise Exception(
                "No gamepad detected. Please connect a gamepad and restart."
            )

        # Use the first available gamepad
        self.gamepad = pygame.joystick.Joystick(0)
        self.gamepad.init()
        print(f"Connected to: {self.gamepad.get_name()}")

        # Initialize serial connection to ESP32
        try:
            self.serial_conn = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
            print(f"Connected to ESP32 on {SERIAL_PORT}")
        except serial.SerialException as e:
            raise Exception(f"Serial connection failed: {e}")

        # Motor control variables
        self.left_rpm = 0
        self.right_rpm = 0

    def read_gamepad(self):
        """Read gamepad inputs and process them"""
        # Process pygame events
        pygame.event.pump()

        # Read left stick for throttle/steering
        # Y-axis for throttle (forward/backward)
        throttle = -self.gamepad.get_axis(
            1
        )  # Negative because forward is negative in many gamepads

        # X-axis for steering (left/right)
        steering = self.gamepad.get_axis(0)

        return throttle, steering

    def calculate_motor_rpms(self, throttle, steering):
        """Calculate motor RPMs based on throttle and steering inputs"""
        # Simple differential steering algorithm
        left_power = throttle - steering
        right_power = throttle + steering

        # Clamp values between -1 and 1
        left_power = max(-1, min(1, left_power))
        right_power = max(-1, min(1, right_power))

        # Scale to RPM range
        self.left_rpm = int(left_power * MAX_RPM)
        self.right_rpm = int(right_power * MAX_RPM)

    def send_command(self):
        """Send command to ESP32 via serial"""
        command = {"left_rpm": self.left_rpm, "right_rpm": self.right_rpm}

        # Convert command to JSON string and add newline as message terminator
        command_str = json.dumps(command) + "\n"

        # Send command
        self.serial_conn.write(command_str.encode())

    def run(self):
        """Main control loop"""
        update_interval = 1.0 / UPDATE_RATE

        try:
            while True:
                loop_start = time.time()

                # Read gamepad
                throttle, steering = self.read_gamepad()

                # Calculate motor RPMs
                self.calculate_motor_rpms(throttle, steering)

                # Send command
                self.send_command()

                # Display current state
                print(
                    f"Throttle: {throttle:.2f}, Steering: {steering:.2f} → Left RPM: {self.left_rpm}, Right RPM: {self.right_rpm}"
                )

                # Sleep to maintain update rate
                elapsed = time.time() - loop_start
                sleep_time = max(0, update_interval - elapsed)
                time.sleep(sleep_time)

        except KeyboardInterrupt:
            print("Controller stopped by user")
        finally:
            # Clean up
            if hasattr(self, "serial_conn") and self.serial_conn.is_open:
                self.serial_conn.close()
            pygame.quit()


if __name__ == "__main__":
    try:
        controller = RoverController()
        controller.run()
    except Exception as e:
        print(f"Error: {e}")
