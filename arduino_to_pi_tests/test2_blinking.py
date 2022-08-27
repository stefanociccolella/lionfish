import serial

import time

serial1 = serial.Serial('/dev/ttyACM0', 9600)

# while True:

serial1.write(b'0')
time.sleep(1)

if (serial1 == 48):
#     while True:
    input = serial1.read()
    print(input.decode("utf-8"))
#         time.sleep(1)
# while True:
    end
    
serial1.write(b'9')
time.sleep(1)
#     while True:
if (serial1 == 57):
    input = serial1.read()
    print(input.decode("utf-8"))
    time.sleep(1)