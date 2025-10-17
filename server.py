from fastapi import FastAPI
from pydantic import BaseModel

app = FastAPI()

class Metadata(BaseModel):
    battery: int

@app.post("/update_metadata")
async def update(metadata: Metadata):
    print(f"Received battery: {metadata.battery}")
    return {"battery": metadata.battery}
