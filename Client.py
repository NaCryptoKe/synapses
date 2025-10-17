from zeroconf import Zeroconf, ServiceBrowser
import socket
import metaData

# add_sevice when a new device is detected
# remove_service when a device leaves the network
# update_service when device info changes but the connection is still valid


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
        print (f"Updating ... ")


# Create Zeroconf instance and listener
zeroconf = Zeroconf()
listener = MyListener()
browser = ServiceBrowser(zeroconf, "_synapses._tcp.local.", listener)

metaData.send_metadata(listener)

try:
    input("Press Enter to exit...\n")
finally:
    zeroconf.close()
