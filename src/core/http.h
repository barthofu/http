#include <sys/socket.h>

#ifndef __HTTP_H
#define __HTTP_H

int processRequest (int client_sockfd, struct sockaddr_storage client_addr);

int processResponse (char *fileName, int client_sockfd, int fdFile);

int processOpenError (int client_sockfd, int fdFile);

int sendResponse (int client_sockfd, char *header, int fdFile);

#endif