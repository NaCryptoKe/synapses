#define _POSIX_C_SOURCE 200809L

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define DEFAULT_PORT 5000
#define MAX_LINE 1024

static void fail(const char *what)
{
    perror(what);
    exit(EXIT_FAILURE);
}

static int read_line(int fd, char *buffer, size_t capacity)
{
    size_t used = 0;
    while (used + 1 < capacity) {
        char ch;
        ssize_t n = recv(fd, &ch, 1, 0);
        if (n == 0)
            break;
        if (n < 0) {
            if (errno == EINTR)
                continue;
            return -1;
        }
        buffer[used++] = ch;
        if (ch == '\n')
            break;
    }
    buffer[used] = '\0';
    return (int)used;
}

static int send_all(int fd, const char *data, size_t length)
{
    size_t sent = 0;
    while (sent < length) {
        ssize_t n = send(fd, data + sent, length - sent, 0);
        if (n < 0) {
            if (errno == EINTR)
                continue;
            return -1;
        }
        sent += (size_t)n;
    }
    return 0;
}

int main(int argc, char **argv)
{
    char *end = NULL;
    long port = argc > 1 ? strtol(argv[1], &end, 10) : DEFAULT_PORT;
    if ((argc > 1 && (*end != '\0' || end == argv[1])) || port < 1 || port > 65535) {
        fprintf(stderr, "Usage: %s [port 1-65535]\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Prevent a disconnected client from terminating the server via SIGPIPE. */
    signal(SIGPIPE, SIG_IGN);

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
        fail("socket");

    int reuse = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
        fail("setsockopt");

    struct sockaddr_in address = {0};
    address.sin_family = AF_INET;
    address.sin_port = htons((unsigned short)port);
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
        fail("bind");
    if (listen(server_fd, 1) < 0)
        fail("listen");

    printf("Listening for one peer on TCP port %ld...\n", port);
    fflush(stdout);

    int peer_fd;
    do {
        peer_fd = accept(server_fd, NULL, NULL);
    } while (peer_fd < 0 && errno == EINTR);
    if (peer_fd < 0)
        fail("accept");

    puts("Peer connected. Type lines; /quit ends the session.");
    char line[MAX_LINE];
    for (;;) {
        int n = read_line(peer_fd, line, sizeof(line));
        if (n < 0)
            fail("recv");
        if (n == 0)
            break;
        printf("Peer: %s", line);
        if (strcmp(line, "/quit\n") == 0 || strcmp(line, "/quit\r\n") == 0)
            break;
        if (send_all(peer_fd, line, (size_t)n) < 0)
            fail("send");
    }

    close(peer_fd);
    close(server_fd);
    puts("Connection closed.");
    return EXIT_SUCCESS;
}
