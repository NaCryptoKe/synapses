#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(void)
{
    struct addrinfo hints, *res;
    int sockfd, new_fd;
    struct sockaddr_storage client_addr;
    socklen_t addr_size;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, "3490", &hints, &res);

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    bind(sockfd, res->ai_addr, res->ai_addrlen);

    freeaddrinfo(res);

    while(1) {
        listen(sockfd, 10);
        printf("Server listening on port 3490... waiting for connections.\n");

        addr_size = sizeof(client_addr);
        new_fd = accept(sockfd, (struct sockaddr*)&client_addr, &addr_size);

        if (new_fd != -1) {
            printf("Client connected! Dedicated communication socket created with FD: %d\n", new_fd);
        }
    }

    close(new_fd);
    close(sockfd);

    return 0;
}
