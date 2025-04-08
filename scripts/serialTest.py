#! /usr/bin/env python3

import serial
import time
import threading
import queue


class SerialTest:
    def __init__(self, port="COM3", baudrate=115200):
        self.ser = serial.Serial(port, baudrate, timeout=1)
        self.running = True
        self.send_queue = queue.Queue()
        self.receive_queue = queue.Queue()

    def send_thread(self):
        while self.running:
            try:
                # Clear output buffer before sending
                self.ser.reset_output_buffer()

                # Generate timestamp and send
                current_time = time.perf_counter_ns()
                message = f"{current_time}\n"
                self.ser.write(message.encode())

                # Store sent message and time for latency calculation
                self.send_queue.put((current_time, message.strip()))

                # Control send rate
                time.sleep(0.5)
            except Exception as e:
                print(f"Send error: {e}")
                time.sleep(1)

    def receive_thread(self):
        while self.running:
            try:
                # Check if data is available to read
                if self.ser.in_waiting > 0:
                    # Read line and timestamp when received
                    response = self.ser.readline().decode("utf-8").rstrip()
                    receive_time = time.perf_counter_ns()

                    if response:
                        self.receive_queue.put((receive_time, response))
            except Exception as e:
                print(f"Receive error: {e}")
                time.sleep(1)

    def process_thread(self):
        while self.running:
            try:
                # Check for received messages
                if not self.receive_queue.empty():
                    receive_time, response = self.receive_queue.get()

                    # Try to match with a sent message
                    if not self.send_queue.empty():
                        send_time, sent_message = self.send_queue.get()
                        latency_ms = (receive_time - send_time) / 1e6
                        print(
                            f"Latency: {latency_ms:.3f} ms | Received: {response}"
                        )
                    else:
                        print(f"Unexpected response: {response}")
            except Exception as e:
                print(f"Process error: {e}")

            # Don't hog the CPU
            time.sleep(0.01)

    def start(self):
        # Clear any existing data
        self.ser.reset_input_buffer()

        # Start threads
        self.send_thread_handle = threading.Thread(target=self.send_thread)
        self.receive_thread_handle = threading.Thread(
            target=self.receive_thread
        )
        self.process_thread_handle = threading.Thread(
            target=self.process_thread
        )

        self.send_thread_handle.daemon = True
        self.receive_thread_handle.daemon = True
        self.process_thread_handle.daemon = True

        self.send_thread_handle.start()
        self.receive_thread_handle.start()
        self.process_thread_handle.start()

    def stop(self):
        self.running = False
        if hasattr(self, "ser") and self.ser.is_open:
            self.ser.close()


if __name__ == "__main__":
    serial_test = SerialTest()
    print("Starting serial test. Press Ctrl+C to stop.")

    try:
        serial_test.start()
        # Keep main thread alive
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print("\nExiting...")
    finally:
        serial_test.stop()
