# Arduino forum 2020 - https://forum.arduino.cc/index.php?topic=714968
import serial
from struct import *
import numpy as np

identity = np.array([
    [-1, 1, 0,0,0,1], 
    [1,-1,0,0,0,1],
    [0,0,1,-1,1,0],
    [0,0,-1,-1,1,0],
    [0,0,1,1,1,0],
    [0,0,-1,1,1,0]
    ]).T

input = np.array([1,1,1,1,0,0])

print(np.dot(input, identity))