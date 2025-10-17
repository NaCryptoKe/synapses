import threading
import time
import requests

def send_metadata(listener):
    while True:
        for name, device in listener.devices.items():
            try:
                url = f"http://{device['ip']}:{device['port']}/update_metadata"
                payload = {"battery": 87}  # example, could be dynamic
                requests.post(url, json=payload, timeout=0.5)
            except Exception as e:
                print(f"Failed to send metadata to {name}: {e}")
        time.sleep(1)  # send every 1 second