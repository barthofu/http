#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>

#include "http.h"
  
int server_create(char *port) {

    struct addrinfo hints, *res;
    int sockfd, error;

    // server setup

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // to tell that we are server side

    if (getaddrinfo(NULL, port, &hints, &res) != 0) {
        perror("getaddrinfo");
        exit(1);
    }

    if ((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) {
        perror("socket");
        exit(1);
    }


    if (bind(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(sockfd, 5) == -1) {
        perror("listen");
        exit(1);
    }

    return sockfd;
}

int server_listen(int sockfd) {

    while (1) {

        struct sockaddr_storage client_addr;
        socklen_t addr_size;
        int client_sockfd;
        
        char buffer[256];
        int n;

        client_sockfd = accept(sockfd, NULL, NULL);
        if (client_sockfd < 0) continue;

        int pid = fork();
        if (pid < 0) {
            close(client_sockfd);
            return -1;
        } else if (pid == 0) {
            // process the request
            processRequest(client_sockfd);

            close(client_sockfd);
            exit(0);
        } else {
            close(client_sockfd);
        }
    }
}