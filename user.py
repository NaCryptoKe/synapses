from fastapi import FastAPI
from pydantic import BaseModel

class User(BaseModel):
    username: str
    password: str

app = FastAPI()
users = []

@app.get('/users/{username}')
async def get_user(username: str):
    for user in users:
        if user["username"] == username:
            return user
    return {"error": "User not found"}

@app.post('/users')
async def create_user(user: User):
    new_user = {"username": user.username, "password": user.password}
    for user in users:
        if user["username"] == new_user["username"]:
            return {"error": "Username already exists"}
    users.append(new_user)
    return new_user

@app.delete('/users/{username}')
async def delete_user(username: str):
    for user in users:
        if user["username"] == username:
            users.remove(user)
            return {"success": True}
    return {"error": "Username not found"}