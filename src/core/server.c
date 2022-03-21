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

    // Setup du serveur

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // Pour définir qu'on est côté serveur et non client

    // On récupère les informations sur le port
    if (getaddrinfo(NULL, port, &hints, &res) != 0) {
        perror("getaddrinfo");
        exit(1);
    }

    // On crée le socket
    if ((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) {
        perror("socket");
        exit(1);
    }

    // Cette fonction permet d'autorisation l'utilisation du port lorsqu'il est déjà utilisé par un processus zombie (afin d'éviter d'attendre 1~2minutes pour pouvoir rebind le serveur après l'avoir fermé)
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");

    // On lie le socket à l'adresse
    if (bind(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
        perror("bind");
        exit(1);
    }

    // On définit le nombre de connexions en attente
    if (listen(sockfd, 5) == -1) {
        perror("listen");
        exit(1);
    }

    return sockfd;
}

int server_listen(int sockfd) {

    while (1) { // On attend une connexion dans la boucle while

        struct sockaddr_storage client_addr;
        socklen_t addr_size;
        int client_sockfd;

        // On récupère les informations sur le client
        client_sockfd = accept(sockfd, (struct sockaddr*) &client_addr, &addr_size);
        if (client_sockfd < 0) continue;

        // On traite la requête du client dans un processus fils
        int pid = fork();

        if (pid < 0) {
            close(client_sockfd);
            return -1;
        } 
        else if (pid == 0) {
            // process the request
            processRequest(client_sockfd, client_addr);
            exit(0);
        }

        close(client_sockfd);
    }
}