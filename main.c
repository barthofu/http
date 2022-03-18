#include "src/core/server.h"
#include "src/core/http.h"
  
#include "config.h"

int main () {

    int sockfd = server_create(LISTEN_PORT);
    server_listen(sockfd);

    return 0;
}