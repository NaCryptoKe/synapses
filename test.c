#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

/*
* int getaddrinfo(  const char *node,  e.g. www.example.com or IP
*                   const char *servive,  e.g. http or port number
*                   const struct addrinfo *hints,
*                   struct addrinfo **res );
*/

int status;
struct addrinfo hints;
struct addrinfo *servinfo;  // will point to the results

memset(&hints, 0, sizeof(hints)); // making sure the struct is empty
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_DGRAM;
hints.ai_flags = AI_PASSIVE;

if ((status = getaddrinfo(NULL, "3490", &hints, &servinfo)) != 0) {
  fprintf(stderr, "gai error: %s\n", gai_strerror(status));
  exit(1);
}

freeadrinfo(servinfo);
