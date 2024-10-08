import pigpio
import time
import struct

# I2C address of the ESP32
I2C_ADDRESS = 0x08

# Initialize pigpio library
pi = pigpio.pi()

if not pi.connected:
    print("Failed to connect to pigpio daemon")
    exit()

# Open I2C bus 1
i2c_handle = pi.i2c_open(1, I2C_ADDRESS)

def set_motor_rpm(motor_index, rpm):
    """
    Send RPM command to the specified motor index.
    :param motor_index: Index of the motor (0, 1, 2, 3)
    :param rpm: Desired RPM value (float)
    """
    if motor_index < 0 or motor_index > 3:
        print("Invalid motor index")
        return

    # Pack the motor index and RPM into bytes
    rpm_bytes = struct.pack('f', rpm)
    data = [motor_index] + list(rpm_bytes)

    # Send the data over I2C
    pi.i2c_write_device(i2c_handle, data)

try:
    while True:
        # Example: Set motor 0 to 100.5 RPM
        set_motor_rpm(0, 100.5)
        time.sleep(1)

        # Example: Set motor 1 to 150.75 RPM
        set_motor_rpm(1, 150.75)
        time.sleep(1)

        # Example: Set motor 2 to 200.25 RPM
        set_motor_rpm(2, 200.25)
        time.sleep(1)

        # Example: Set motor 3 to 50.5 RPM
        set_motor_rpm(3, 50.5)
        time.sleep(1)

except KeyboardInterrupt:
    print("Stopping script")

finally:
    # Close I2C handle and terminate pigpio
    pi.i2c_close(i2c_handle)
    pi.stop()