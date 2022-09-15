from pathlib import Path
from fastapi import FastAPI
from fastapi import Request, Response
from fastapi import Header
from fastapi.templating import Jinja2Templates
import picamera


app = FastAPI()
templates = Jinja2Templates(directory="templates")
CHUNK_SIZE = 1024*1024
video_path = Path("Show Me the Money!   Jerry Maguire 1 8) Movie CLIP (1996) HD-FFrag8ll85w.webm")
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

@app.get("/")
async def read_root(request: Request):
    return templates.TemplateResponse("index.htm", context={"request": request})


@app.get("/video")
async def video_endpoint(range: str = Header(None)):
    
    headers = {
        'Age': 0,
        'Cache-Control': 'no-cache, private',
        'Pragma':'no-cache',
        'Content-Type':'multipart/x-mixed-replace; boundary=FRAME'

    }
    return Response(data, status_code=206, headers=headers, media_type="video/webm")


with picamera.PiCamera(resolution='640x480', framerate=24) as camera:
    output = StreamingOutput()
    #Uncomment the next line to change your Pi's Camera rotation (in degrees)
    #camera.rotation = 90
    camera.start_recording(output, format='mjpeg')
    try:
        while True:
            pass
    except:
        camera.stop_recording()