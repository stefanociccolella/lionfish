import serial
import time


ser = serial.Serial('/dev/ttyACM0', 9600)

while True:

    input = ser.read()
    input = input.decode("utf-8")
    print ((input))
    ser.write(b"A")
    time.sleep(1)