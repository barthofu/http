#ifndef __HTTP_H
#define __HTTP_H

int processRequest(int client_sockfd);

int processResponse (char *fileName, int client_sockfd, int fdFile);

int processOpenError (int client_sockfd, int fdFile);

#endif