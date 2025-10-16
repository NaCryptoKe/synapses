from fastapi import FastAPI, UploadFile, File
from fastapi.responses import FileResponse
import shutil
import os
import mimetypes

app = FastAPI()

UPLOAD_DIR = "./uploads"

os.makedirs(UPLOAD_DIR, exist_ok=True)

@app.post("/upload")
async def upload_file(file: UploadFile = File(...)):
    file_path = os.path.join(UPLOAD_DIR, file.filename)
    with open(file_path, "wb") as buffer:
        shutil.copyfileobj(file.file, buffer)
    return {"filename": file.filename, "message": "File uploaded successfully"}


@app.get("/files/{filename}")
async def get_file(filename: str):
    filepath = os.path.join(UPLOAD_DIR, filename)
    if os.path.isfile(filepath):
        return FileResponse(filepath, media_type="text/plain")
    return {"error": "File not found"}

@app.get("/list-files")
async def list_files():
    return os.listdir(UPLOAD_DIR)

