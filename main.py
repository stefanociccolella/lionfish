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

class gamepad(BaseModel):
    axes: list[float]
    buttons: list[int]

app = FastAPI()

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
arduino = serial.Serial(port='/dev/ttyUSB0', baudrate=115200, timeout=.1)

@app.get("/")
async def read_root(request: Request):
    return templates.TemplateResponse("index.htm", context={"request": request})

# @app.get("/esp")
# async def write_read(position):
#     arduino.write(bytes(position, 'utf-8'))
#     time.sleep(0.05)
#     data = arduino.readline()
#     return str(data)

@app.post("/controller_status")
async def controller_data(gamepad: gamepad):
    # print(np.append(np.array(gamepad.axes),gamepad.buttons[4], gamepad.buttons[6]))
    control = np.append(gamepad.axes, [gamepad.buttons[4], gamepad.buttons[6]])
    control = np.round(control, decimals = 2)
    print(control.astype(single).tobytes())
    arduino.write(control.astype(single).tobytes())
    # while True:                                                          #random test, that whether data is updated
    time.sleep(.02)#delay
    dat=arduino.readline()#read a line data

    if dat!=b''and dat!=b'\r\n':
        dats=str(dat)
        dat1=dats.replace("b","")
        dat2=dat1.replace("'",'')
        dat3=dat2[:-4]
        list_=ast.literal_eval(dat3) #list_ value can you use in program
        print(dat3)
    # print(control)
    # print(control.tobytes())


# TODO bring USB ethernet dongle

# check to see if this is the main thread of execution
if __name__ == '__main__':
    
    global count_keep_alive
    p = Process(target=start_camera)
    p.start()
    uvicorn.run(app, host="0.0.0.0", port=8000, access_log=False)
    p.close()
