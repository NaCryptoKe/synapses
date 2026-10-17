# Simple point-to-point TCP example in C

This small POSIX sockets example connects one client directly to one server over TCP. The server accepts one connection, prints each line from the client, and echoes it back. Type `/quit` at the client to end the session.

## Build

On Linux or macOS, compile each program in this directory:

```sh
cc -Wall -Wextra -pedantic -std=c11 -o p2p_server p2p_server.c
cc -Wall -Wextra -pedantic -std=c11 -o p2p_client p2p_client.c
```

## Try it on one computer

In terminal 1:

```sh
./p2p_server
```

In terminal 2:

```sh
./p2p_client
```

Both use TCP port 5000 by default. The client connects to `127.0.0.1` by default, which keeps the first test on the same computer.

## Connect two computers directly over an IP network

Start the server on the computer that will listen:

```sh
./p2p_server 5000
```

On the client computer, connect to the server computer's reachable IPv4 address:

```sh
./p2p_client 203.0.113.10 5000
```

Replace `203.0.113.10` with the server's actual address. Both computers need an IP route between them, and the server's firewall must allow inbound TCP traffic on that port. Across the public internet, a server behind a home router may also need port forwarding; carrier-grade NAT can prevent direct inbound connections. This learning example has no encryption or authentication, so keep it on loopback or a trusted network.

The wire format is one UTF-8 or ASCII text line ending in newline; the server echoes each line. TCP is a byte stream, so the newline provides the message boundary in this example.
