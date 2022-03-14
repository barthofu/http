#ifndef __SERVER_H
#define __SERVER_H

int server_create(char *port);

int server_listen(int sockfd);

#endif