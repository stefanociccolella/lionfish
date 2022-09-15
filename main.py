from pathlib import Path
from fastapi import FastAPI
from fastapi import Request, Response
from fastapi import Header
from fastapi.templating import Jinja2Templates


app = FastAPI()
templates = Jinja2Templates(directory="templates")
CHUNK_SIZE = 1024*1024
video_path = Path("Show Me the Money!   Jerry Maguire 1 8) Movie CLIP (1996) HD-FFrag8ll85w.webm")


@app.get("/")
async def read_root(request: Request):
    return templates.TemplateResponse("index.htm", context={"request": request})


@app.get("/video")
async def video_endpoint(range: str = Header(None)):
    start, end = range.replace("bytes=", "").split("-")
    start = int(start)
    end = int(end) if end else start + CHUNK_SIZE
    with open(video_path, "rb") as video:
        video.seek(start)
        data = video.read(end - start)
        filesize = str(video_path.stat().st_size)
        headers = {
            'Content-Range': f'bytes {str(start)}-{str(end)}/{filesize}',
            'Accept-Ranges': 'bytes'
        }
        return Response(data, status_code=206, headers=headers, media_type="video/webm")
