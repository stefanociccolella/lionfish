# Web streaming example
# Source code from the official PiCamera package
# http://picamera.readthedocs.io/en/latest/recipes2.html#web-streaming

import io
import picamera
import logging
import socketserver
from threading import Condition
from http import server
from fastapi import FastAPI #, Request
from fastapi.responses import StreamingResponse, HTMLResponse
from picamera import PiCamera
from io import BytesIO
import requests
# from videostreamtest import run_camera

app = FastAPI()

PAGE=f"""\
<html>
<head>
<title>Raspberry Pi - Surveillance Camera</title>
</head>
<body>
<center><h1>Raspberry Pi - Surveillance Camera</h1></center>
<center><img src="stream.mjpg" width="640" height="480"></center>
"""

from fastapi import FastAPI, Request

app = FastAPI()


@app.get("/index.html")
async def main():
    return {"raw_url"}

# @app.get("/foo/bar/{rand_int}/foo-bar/")
# async def main(rand_int: int, request: Request):
#     print(request.url._url)
#     print(request.base_url)
#     return {"raw_url": request.url._url}