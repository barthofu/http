#ifndef __HTTP_H
#define __HTTP_H

int processGETRequest(int client_sockfd);

int processResponse (char *fileName, int client_sockfd, int fdFile);

#endif