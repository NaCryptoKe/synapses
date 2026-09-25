#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    const char *message = "Hello Server";
    struct sockaddr_in servaddr;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    
    // Modern IP string parsing
    if (inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0) {
        perror("Invalid address / Address not supported");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Send only actual string length
    if (sendto(sockfd, message, strlen(message), 0, 
               (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("sendto failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    socklen_t len = sizeof(servaddr);
    ssize_t n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, 
                         (struct sockaddr *)&servaddr, &len);
    if (n < 0) {
        perror("recvfrom failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    buffer[n] = '\0';
    printf("Server response: %s\n", buffer);

    close(sockfd);
    return 0;
}
