from pathlib import Path
from fastapi import FastAPI
from fastapi import Request
from fastapi.responses import StreamingResponse
from fastapi import Header
from fastapi.templating import Jinja2Templates
import picamera
from threading import Condition
import io


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

    #TODO write a __iter__ function and __next__ function to turn the class into an iterator that yields frames


@app.get("/")
async def read_root(request: Request):
    return templates.TemplateResponse("index.htm", context={"request": request})


@app.get("/video")
async def video_endpoint(range: str = Header(None)):
    # start, end = range.replace("bytes=", "").split("-")
    # start = int(start)
    # end = int(end) if end else start + CHUNK_SIZE
    # with open(video_path, "rb") as video:
    #     video.seek(start)
    #     data = video.read(end - start)
    #     filesize = str(video_path.stat().st_size)
        # headers = {
        #     # 'Content-Range': f'bytes {str(start)}-{str(end)}/{filesize}',
        #     # 'Accept-Ranges': 'bytes'
        # }
        return StreamingResponse(data, status_code=206, 
        # headers=headers, 
        media_type="video/webm")


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