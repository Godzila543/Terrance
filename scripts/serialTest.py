#! /usr/bin/env python3

import serial
import time

if __name__ == "__main__":
    ser = serial.Serial("/dev/ttyUSB0", 115200, timeout=1)
    ser.reset_input_buffer()

    # Latency test
    while True:
        # Clear any remaining data in the buffers
        ser.reset_input_buffer()
        ser.reset_output_buffer()

        # Add a newline character to ensure proper line termination
        currentTime = time.perf_counter_ns()
        ser.write(f"{currentTime}\n".encode())

        response = ser.readline().decode("utf-8").rstrip()
        latency_ms = (time.perf_counter_ns() - currentTime) / 1e6

        print(f"Latency: {latency_ms:.3f} ms | Response: {response}")

        response = ser.readline().decode("utf-8").rstrip()
        if response:
            print(f"Response: {response}")
        time.sleep(0.5)
