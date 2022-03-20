#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

int logFile (char *fileName, FILE *fd) {
    fprintf(fd, fileName, strlen(fileName));
    return 0;
}


int logTime (FILE *fd) {

    time_t myTime;
    struct tm * timeInfo; 
    
    time(&myTime);
    timeInfo = localtime(&myTime);
    
    fprintf(fd, "%d/%d/%d - %d:%d | ", 
        timeInfo->tm_mday, timeInfo->tm_mon + 1, timeInfo->tm_year + 1900, 
        timeInfo->tm_hour, timeInfo->tm_min
    );

    return 0;
}


int logIp (struct sockaddr_storage client_addr, FILE *fd) {

    struct sockaddr_in *sin4 = (struct sockaddr_in *) &client_addr;
    unsigned char *ipv4 = (unsigned char *) &sin4->sin_addr.s_addr;

    struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *) &client_addr;
    unsigned char *ipv6 = (unsigned char *) &sin6->sin6_addr.s6_addr;

    if (client_addr.ss_family == AF_INET) {
        fprintf(fd, "%d.%d.%d.%d | ", ipv4[0], ipv4[1], ipv4[2], ipv4[3]);
    } else if (client_addr.ss_family == AF_INET6) {
        fprintf(fd, "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x | ",
            ipv6[0], ipv6[1], ipv6[2], ipv6[3],
            ipv6[4], ipv6[5], ipv6[6], ipv6[7],
            ipv6[8], ipv6[9], ipv6[10], ipv6[11],
            ipv6[12], ipv6[13], ipv6[14], ipv6[15]);
    }

    return 0;
}


int logConnection (struct sockaddr_storage client_addr, char *fileName) {

    FILE *fd;
    fd = fopen("logs.txt", "a");
    
    logTime(fd);
    logIp(client_addr, fd);
    logFile(fileName, fd);
    fprintf(fd, "\n", 1);

    fclose(fd);

    return 0;
}