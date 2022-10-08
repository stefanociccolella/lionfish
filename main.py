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
from pydantic import BaseModel

class gamepad(BaseModel):
    axes: list[int]
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
# arduino = serial.Serial(port='/dev/ttyUSB0', baudrate=115200, timeout=.1)

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
    print(gamepad)


# TODO bring USB ethernet dongle

# check to see if this is the main thread of execution
if __name__ == '__main__':
    
    global count_keep_alive
    p = Process(target=start_camera)
    p.start()
    uvicorn.run(app, host="0.0.0.0", port=8000, access_log=False)
    p.close()
