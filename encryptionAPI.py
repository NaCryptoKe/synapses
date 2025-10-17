from fastapi import FastAPI
from pydantic import BaseModel
from encryption import fernet
import encrypt
import json

app = FastAPI()

class User(BaseModel):
    username: str
    device: str

@app.post('/auth/token')
async def generate_token(user: User):
    token = encrypt.encrypt_dict(user.model_dump())
    return {"token", token.decode()}