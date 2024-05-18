# Authors: Github Copilot, Colin Brown
# Python
import socket
import json
import queue
import threading
from inputs import devices

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


# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Bind the socket to the port
server_address = ("0.0.0.0", 54535)
sock.bind(server_address)
sock.settimeout(1)
sock.listen(1)

try:
    while True:
        # Wait for a connection
        print("Waiting for a connection...")
        while True:
            try:
                connection, client_address = sock.accept()
                break
            except socket.timeout:
                continue
        print("\033[32m" + f"Connected to {client_address}" + "\033[0m")
        try:
            while True:
                if not gamepad_events.empty():
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
                    # Send data
                    if data["axes"] or data["buttons"]:
                        connection.sendall(
                            json.dumps(data).encode("utf-8") + b"\n"
                        )
        except ConnectionAbortedError:
            print("\033[31m" + "Connection aborted." + "\033[0m")
        except Exception as e:
            print("\033[33m" + f"Error: {e}" + "\033[0m")
        finally:
            # Clean up the connection
            connection.close()
except KeyboardInterrupt:
    print("Server is shutting down...")
finally:
    sock.close()
    stop_reading.set()
    gamepad_thread.join()

    print("Server has shut down.")
