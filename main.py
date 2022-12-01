from pickletools import float8
from fastapi import FastAPI
from fastapi import Request
from fastapi import Header
from fastapi.templating import Jinja2Templates
import time
from multiprocessing import Process
from pydantic import Json
import uvicorn
from start_camera import start_camera
import serial
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel, BaseConfig
import numpy as np
from numpy import single
import ast

# BaseConfig.arbitrary_types_allowed = True

# global sensor_data = []
class gamepad(BaseModel):
    axes: list[float]
    buttons: list[float]


app = FastAPI()
app.sensor_data = []

origins = [
    "http://localhost",
    "http://localhost:8000",
]

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)
templates = Jinja2Templates(directory="templates")
kill_cam = 0
arduino = serial.Serial(port="/dev/ttyUSB0", baudrate=115200, timeout=0.1)


@app.get("/")
async def read_root(request: Request):
    return templates.TemplateResponse("index.htm", context={"request": request})


# random comments
# @app.get("/esp")
# async def write_read(position):
#     arduino.write(bytes(position, 'utf-8'))
#     time.sleep(0.05)
#     data = arduino.readline()
#     return str(data)


@app.post("/controller_status")
async def controller_data(gamepad: gamepad):
    print(gamepad)
    # t1 = time.time_ns()
    # print(np.append(np.array(gamepad.axes),gamepad.buttons[4], gamepad.buttons[6]))
    control = np.append(
        gamepad.axes,
        [
            # The buttons are out of order to make the identity simplier
            gamepad.buttons[4], # LB Button
            gamepad.buttons[6], # LT Button
            gamepad.buttons[1], # B Button
            gamepad.buttons[3], # Y Button
            gamepad.buttons[5], # RB Button
        ],
    )
    control = np.round(control, decimals=2)
    print(control)
    identity = np.array(
        [
            [0, 0, 0, -1, -1, 1, 0, 0, 0],
            [0, 0, 0, -1, 1, -1, 0, 0, 0],
            [1, 1, 1, 0, 0, 0, 0, 0, 0],
            [1, -1, 1, 0, 0, 0, 0, 0, 0],
            [-1, -1, 1, 0, 0, 0, 0, 0, 0],
            [-1, 1, 1, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 1, 0, 0], # lazer
            [0, 0, 0, 0, 0, 0, 0, 1, 0], # light
            [0, 0, 0, 0, 0, 0, 0, 0, 1], # harpoon
        ]
    ).T  # rewrite this so its already transposed
    # print(identity)
    control = np.dot(control, identity)
    # print('from pi', np.array2string(control.astype(single),separator=',').encode('utf-8'))
    # arduino.write(control.astype(single).tobytes)
    print(control)

    arduino.write(
        np.array2string(control.astype(single), separator=",").encode("utf-8")
    )
    # while True:                                                          #random test, that whether data is updated
    time.sleep(0.1)  # delay
    dat = arduino.readline()  # read a line data
    with open("data.json", "w") as f:
        f.write(dat.decode())
    # print('from esp', dat)

    # print('from esp', dat[0:-2].decode().split(","))
    # fromESP = np.array(dat[0:-2].decode().split(","))
    # Labels = ['leak', 'internal_temp', 'pressure','water_temperature','depth','altitude','acceleration_x','acceleration_y','acceleration_z','gyroscope_x','gyroscope_y','gyroscope_z','magnometer_x','magnometer_y','magnometer_z','IMU_temp']
    # toDisk = {Labels[i]: fromESP[i] for i in range(len(Labels))}
    # print(toDisk)

    # np.array(dat[0:-2].decode().split(",")).tofile('fid.csv', sep=',')
    # print(time.time_ns() - t1)
    # print(np.frombuffer(dat, count=3))
    # print(control)
    # print(control.tobytes())


@app.get("/get_sensors")
async def get_sensors():
    with open("data.json", "r") as f:
        return f.read()


# TODO bring USB ethernet dongle

# check to see if this is the main thread of execution
if __name__ == "__main__":

    global count_keep_alive
    p = Process(target=start_camera)
    p.start()
    uvicorn.run(app, host="0.0.0.0", port=8000, access_log=False)
    p.close()
