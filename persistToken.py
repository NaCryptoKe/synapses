import json
from encrypt import encrypt_dict, decrypt_dict

users = [
    {"username": "nao", "device": "laptop"},
    {"username": "axum", "device": "phone"},
    {"username": "synapses", "device": "tablet"}
]

# Encrypt all users
tokens = [encrypt_dict(u) for u in users]

# Save tokens to JSON file (convert bytes → string)
with open("encrypted_users.json", "w") as f:
    json.dump([t.decode() for t in tokens], f)

# Reload tokens from file (convert string → bytes)
with open("encrypted_users.json", "r") as f:
    loaded_tokens = [t.encode() for t in json.load(f)]

# Decrypt loaded tokens
restored_users = [decrypt_dict(t) for t in loaded_tokens]

print("Restored Users:", restored_users)
print("Match Original:", restored_users == users)