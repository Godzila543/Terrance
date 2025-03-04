#! /usr/bin/env python3

import serial
import time

if __name__ == "__main__":
    ser = serial.Serial("/dev/ttyUSB0", 115200, timeout=1)
    ser.reset_input_buffer()

    # Latency test
    while True:
        currentTime = time.perf_counter_ns()
        ser.write(str(currentTime).encode())
        response = ser.readline().decode("utf-8").rstrip()
        # print(f"Latency: {(time.perf_counter_ns() - currentTime)/1000} ms")
        print(f"Time: {currentTime}")
        time.sleep(0.5)
