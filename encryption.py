from cryptography.fernet import Fernet
key_path = "synapses.key"

try:
    key = open (key_path, "rb").read()
except FileNotFoundError:
    key = Fernet.generate_key()
    open(key_path, "wb").write(key)

fernet = Fernet(key)
print(f"Key Loaded: {key.decode()}") # decode used for changing byte to utf-8