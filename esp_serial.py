import serial
import time

# Configure serial connection
port = "COM4"
baud_rate = 115200

try:
    esp32 = serial.Serial(port, baud_rate, timeout=1)
    time.sleep(2)  # Wait for ESP32 to reset

    print("Connected to ESP32!")

    # Send a message
    esp32.write(b'Hello ESP32!\n')
    print("Message sent to ESP32.")

    # Read response
    while True:
        if esp32.in_waiting > 0:
            response = esp32.readline().decode('utf-8').strip()
            print(f"Received: {response}")
except Exception as e:
    print(f"Error: {e}")
finally:
    if 'esp32' in locals() and esp32.is_open:
        esp32.close()
        print("Connection closed.")
