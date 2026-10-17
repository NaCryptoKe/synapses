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

int main(int argc, char **argv)
{
    if (argc > 3) {
        fprintf(stderr, "Usage: %s [server-ip [port]]\n", argv[0]);
        return EXIT_FAILURE;
    }
    const char *ip = argc > 1 ? argv[1] : "127.0.0.1";
    char *end = NULL;
    long port = argc > 2 ? strtol(argv[2], &end, 10) : DEFAULT_PORT;
    if ((argc > 2 && (*end != '\0' || end == argv[2])) || port < 1 || port > 65535) {
        fprintf(stderr, "Port must be a number from 1 to 65535.\n");
        return EXIT_FAILURE;
    }

    signal(SIGPIPE, SIG_IGN);
    int peer_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (peer_fd < 0)
        fail("socket");

    struct sockaddr_in server = {0};
    server.sin_family = AF_INET;
    server.sin_port = htons((unsigned short)port);
    if (inet_pton(AF_INET, ip, &server.sin_addr) != 1) {
        fprintf(stderr, "Invalid IPv4 address: %s\n", ip);
        return EXIT_FAILURE;
    }
    if (connect(peer_fd, (struct sockaddr *)&server, sizeof(server)) < 0)
        fail("connect");

    printf("Connected to %s:%ld. Type a line; /quit ends the session.\n", ip, port);
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), stdin) != NULL) {
        size_t length = strlen(line);
        if (send_all(peer_fd, line, length) < 0)
            fail("send");
        if (strcmp(line, "/quit\n") == 0 || strcmp(line, "/quit\r\n") == 0)
            break;

        char reply[MAX_LINE];
        int n = read_line(peer_fd, reply, sizeof(reply));
        if (n < 0)
            fail("recv");
        if (n == 0) {
            puts("Server closed the connection.");
            break;
        }
        printf("Server echoed: %s", reply);
    }

    close(peer_fd);
    return EXIT_SUCCESS;
}
