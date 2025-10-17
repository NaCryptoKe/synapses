from zeroconf import Zeroconf, ServiceBrowser
import socket

devices = {}

# Get local IP
ip = socket.gethostbyname(socket.gethostname())

port = 9000

class MyListener():
    def remove_service(self, zeroconf, type, name):
        print(f"Service {name} removed")

    def add_service(self, zeroconf, type, name):
        info = zeroconf.get_service_info(type, name)
        if info:
            ip = socket.inet_ntoa(info.addresses[0])
            self.devices[name] = {"ip": ip, "port": port, "info": info}
            print(f"Device added: {name} at {ip}:{port}")


zeroconf = Zeroconf()
listener = MyListener()
browser = ServiceBrowser(zeroconf, "_synapses._tcp.local.", listener)

try:
    input("Press Enter to exit...\n")
finally:
    zeroconf.close()
