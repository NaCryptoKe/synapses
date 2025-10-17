# Service Name: _synapses._tcp.local.
# Server: anounces itself
# Client: listens for services and prints IP + Port

# This is first step before devices handshake, before BLE or Wi-Fi direct

from zeroconf import ServiceInfo, Zeroconf
import socket

# Get local IP
ip = socket.gethostbyname(socket.gethostname())

# Define service info
info = ServiceInfo(
    "_synapses._tcp.local.",
    "SynapsesLaptop._synapses._tcp.local.",
    addresses=[socket.inet_aton(ip)],
    port=12355,
    properties={
        "version": 0.1,
        "device": "SynapsesServer",
        #Max size of 1KB
    },
    server="synapses.local."
)

zeroconf = Zeroconf()
print(f"Registering service on {ip}:{info.port}")
zeroconf.register_service(info)

try:
    input("Press Enter to exit...\n")
finally:
    zeroconf.unregister_service(info)
    zeroconf.close()
