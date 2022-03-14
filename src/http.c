#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "parser.h" 

int processGETRequest (int client_sockfd) {

    int nbOctets, fdFile;
    char buffer[1000], fileName[1000];

    // bad request error
    char error400[]="HTTP/1.1 400 BAD REQUEST\r\nContent-Type: text/html\r\n\r\n";

    // recv request
    if (recv(client_sockfd, buffer, sizeof(buffer) * sizeof(char), 0) < 0) perror("recv");

    // parse request
    if (parseRequest(buffer, sizeof(buffer), fileName, sizeof(fileName)) == -1) {
        
        // if the request is invalid, we send an error 400
        if (send(client_sockfd, error400, sizeof(error400) * sizeof(char), 0) < 0) perror("send");

		if ((fdFile = open("file400.html", O_RDONLY)) < 0) perror("Erreur open");

		while ((nbOctets = read(fdFile, buffer, 100)) > 0) {
			if (send(client_sockfd, buffer, nbOctets , 0) < 0) perror (" Erreur send ");
		}
    }
	else {		
		if ((fdFile = open(fileName, O_RDONLY)) < 0) perror("Erreur open"); // TODO : make a 404 response process 
		else processResponse(fileName, client_sockfd, fdFile);
	}

	close(client_sockfd);

}


int processResponse (char *fileName, int client_sockfd, int fdFile) {

    int nbOctets;
    char buffer[1000];

    char header200[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
 
    // send header
    if (send(client_sockfd, header200, sizeof(header200) * sizeof(char), 0) < 0) perror("send");

    // TODO : send file
}