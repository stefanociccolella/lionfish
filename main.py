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


app = FastAPI()
templates = Jinja2Templates(directory="templates")
kill_cam = 0
count_keep_alive = 30

@app.get("/")
async def read_root(request: Request):
    return templates.TemplateResponse("index.htm", context={"request": request})


# TODO add a keep alive function and request this in javascript 


def start_camera():
    # Web streaming example
    # Source code from the official PiCamera package
    # http://picamera.readthedocs.io/en/latest/recipes2.html#web-streaming

    import io
    import picamera
    import logging
    import socketserver
    from threading import Condition
    from http import server

    class StreamingOutput(object):
        def __init__(self):
            self.frame = None
            self.buffer = io.BytesIO()
            self.condition = Condition()

        def write(self, buf):
            if buf.startswith(b'\xff\xd8'):
                # New frame, copy the existing buffer's content and notify all
                # clients it's available
                self.buffer.truncate()
                with self.condition:
                    self.frame = self.buffer.getvalue()
                    self.condition.notify_all()
                self.buffer.seek(0)
            return self.buffer.write(buf)

    class StreamingHandler(server.BaseHTTPRequestHandler):
        def do_GET(self):
            if self.path == '/stream.mjpg':
                self.send_response(200)
                self.send_header('Age', 0)
                self.send_header('Cache-Control', 'no-cache, private')
                self.send_header('Pragma', 'no-cache')
                self.send_header('Content-Type', 'multipart/x-mixed-replace; boundary=FRAME')
                self.end_headers()
                try:
                    while True:
                        with output.condition:
                            output.condition.wait()
                            frame = output.frame
                        self.wfile.write(b'--FRAME\r\n')
                        self.send_header('Content-Type', 'image/jpeg')
                        self.send_header('Content-Length', len(frame))
                        self.end_headers()
                        self.wfile.write(frame)
                        self.wfile.write(b'\r\n')
                except Exception as e:
                    logging.warning(
                        'Removed streaming client %s: %s',
                        self.client_address, str(e))
            else:
                self.send_error(404)
                self.end_headers()

    class StreamingServer(socketserver.ThreadingMixIn, server.HTTPServer):
        allow_reuse_address = True
        daemon_threads = True

    with picamera.PiCamera(resolution='640x480', framerate=24) as camera:
        output = StreamingOutput()
        #Uncomment the next line to change your Pi's Camera rotation (in degrees)
        #camera.rotation = 90
        camera.start_recording(output, format='mjpeg')
        try:
            address = ('', 7000)
            server = StreamingServer(address, StreamingHandler)
            server.serve_forever()
        except:
            camera.stop_recording()



def manager_keep_alive(p):
    global count_keep_alive
    while count_keep_alive:
        time.sleep(1)
        print(count_keep_alive)
        count_keep_alive -= 1
    p.kill()
    time.sleep(.5)
    p.close()

# check to see if this is the main thread of execution
if __name__ == '__main__':

    p = Process(target=start_camera)
    p.start()
    threading.Thread(target=manager_keep_alive, args=(p,)).start()
    # start the flask app
    uvicorn.run(app, host="0.0.0.0", port=8000, access_log=False)
