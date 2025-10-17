# metadata.py (snippet)
import time
import requests
import pyperclip  # pip install pyperclip

def send_clipboard(listener):
    while True:
        for name, device in listener.devices.items():
            try:
                clipboard_text = pyperclip.paste()
                url = f"http://{device['ip']}:{device['port']}/update_metadata"
                payload = {"clipboard": clipboard_text}
                requests.post(url, json=payload, timeout=2)
            except Exception as e:
                print(f"Failed to send clipboard to {name}: {e}")
        time.sleep(5)
