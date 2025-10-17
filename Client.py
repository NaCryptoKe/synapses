from zeroconf import Zeroconf, ServiceBrowser
import socket
import threading
import metaData

class MyListener:
    def __init__(self):
        self.devices = {}

    def remove_service(self, zeroconf, type, name):
        if name in self.devices:
            print(f"Device removed: {name}")
            del self.devices[name]

    def add_service(self, zeroconf, type, name):
        info = zeroconf.get_service_info(type, name)
        if info:
            ip = socket.inet_ntoa(info.addresses[0])
            port = info.port
            self.devices[name] = {"ip": ip, "port": port, "info": info}
            print(f"Device added: {name} at {ip}:{port}")

    def update_service(self, zeroconf, type, name):
        info = zeroconf.get_service_info(type, name)
        if info:
            ip = socket.inet_ntoa(info.addresses[0])
            port = info.port
            self.devices[name] = {"ip": ip, "port": port, "info": info}
            print(f"Device updated: {name} at {ip}:{port}")


# Zeroconf setup
zeroconf = Zeroconf()
listener = MyListener()
browser = ServiceBrowser(zeroconf, "_synapses._tcp.local.", listener)

# Start sending metadata in a separate thread
threading.Thread(target=metaData.send_metadata, args=(listener,), daemon=True).start()

try:
    input("Press Enter to exit...\n")
finally:
    zeroconf.close()
