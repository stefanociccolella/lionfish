from pathlib import Path
from fastapi import FastAPI
from fastapi import Request
from fastapi.responses import StreamingResponse
from fastapi import Header
from fastapi.templating import Jinja2Templates
import picamera
from threading import Condition
import io
import logging
import socketserver
from http import server
import time
from multiprocessing import Process
import threading
import uvicorn
from start_camera import start_camera
import serial


app = FastAPI()
templates = Jinja2Templates(directory="templates")
kill_cam = 0
arduino = serial.Serial(port='/dev/ttyUSB0', baudrate=115200, timeout=.1)

@app.get("/")
async def read_root(request: Request):
    return templates.TemplateResponse("index.htm", context={"request": request})

@app.get("/esp")
async def write_read(position):
    arduino.write(bytes(position, 'utf-8'))
    time.sleep(0.05)
    data = arduino.readline()
    return data

# TODO bring USB ethernet dongle

# check to see if this is the main thread of execution
if __name__ == '__main__':
    
    global count_keep_alive
    p = Process(target=start_camera)
    p.start()
    uvicorn.run(app, host="0.0.0.0", port=8000, access_log=False)
    p.close()
