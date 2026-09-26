#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(void) {
    struct addrinfo hints, *res, *p;
    int sockfd;
    int status;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo("127.0.0.1", "3490", &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 1;
    }

    for (p = res; p != NULL; p = p->ai_next) {
        // Create a socket
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd < 0) {
            continue;   // Failed try next address
        }

        // Connect to server
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == 0) {
            printf("Successfully connected to server on port 3490!\n");
            break; // Success! Exit Loop
        }

        close(sockfd);
    }

    if (p == NULL) {
        fprintf(stderr, "Failed to connect to server\n");
        return 2;
    }

    freeaddrinfo(res);

    close(sockfd);
    return 0;
}