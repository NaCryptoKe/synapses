import json
from encryption import fernet


def encrypt_dict(data: dict) -> bytes:
    return fernet.encrypt(json.dumps(data).encode())

def decrypt_dict(data: bytes) -> dict:
    return json.loads(fernet.decrypt(data).decode())