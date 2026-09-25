#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int main() {
    int listenfd;
    char buffer[BUFFER_SIZE];
    const char *message = "Hello Client";
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;

    // Create UDP socket
    if ((listenfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Bind socket
    if (bind(listenfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    len = sizeof(cliaddr);
    
    // Reserve 1 byte for null terminator
    ssize_t n = recvfrom(listenfd, buffer, sizeof(buffer) - 1, 0, 
                         (struct sockaddr *)&cliaddr, &len);
    if (n < 0) {
        perror("recvfrom failed");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    buffer[n] = '\0';
    printf("Client says: %s\n", buffer);

    // Send response
    if (sendto(listenfd, message, strlen(message), 0, 
               (struct sockaddr *)&cliaddr, len) < 0) {
        perror("sendto failed");
    }

    close(listenfd);
    return 0;
}
