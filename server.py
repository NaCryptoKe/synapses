# server.py (snippet)
from fastapi import FastAPI
from pydantic import BaseModel

app = FastAPI()

class Metadata(BaseModel):
    clipboard: str

@app.post("/update_metadata")
async def update(metadata: Metadata):
    print(f"Received clipboard: {metadata.clipboard}")
    return {"received": metadata.clipboard}
