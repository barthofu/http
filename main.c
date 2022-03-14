#include "src/server.h"
#include "src/http.h"
  
int main () {

    int sockfd = server_create("2000");
    server_listen(sockfd);

    


    return 0;
}