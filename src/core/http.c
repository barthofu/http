#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "../utils/parser.h" 
#include "../utils/file.h" 
#include "../../config.h"

int sendResponse (int client_sockfd, char *header, int fdFile) {

	char buffer[1000];
	int nbOctets;

	if (send(client_sockfd, header, sizeof(header) * sizeof(char), 0) < 0) perror("send");

	while ((nbOctets = read(fdFile, buffer, 100)) > 0) {
		if (send(client_sockfd, buffer, nbOctets, 0) < 0) perror("send");
	}

	close(fdFile);
	return 0;
}


int processResponse (char *fileName, int client_sockfd, int fdFile) {

	if (strstr(fileName, ".html")) sendResponse(client_sockfd, HEADER_HTML, fdFile);
	else if (strstr(fileName, ".png")) sendResponse(client_sockfd, HEADER_PNG, fdFile);
	else if (strstr(fileName, ".jpg")) sendResponse(client_sockfd, HEADER_JPG, fdFile);
	else {
		fprintf(stderr, "Erreur processResponse(): le fichier %s n'est pas reconnu\n", fileName);
		return -1;
	}
}


int processRequest (int client_sockfd) {

    int nbOctets, fdFile;
    char buffer[1000], fileName[1000];

    // recv request
    if (recv(client_sockfd, buffer, sizeof(buffer) * sizeof(char), 0) < 0) perror("recv");

    // parse request
    if (parseRequest(buffer, sizeof(buffer), fileName, sizeof(fileName)) == -1) {
        
        // if the request is invalid, we send an error 400
        if (send(client_sockfd, HEADER_400, sizeof(HEADER_400) * sizeof(char), 0) < 0) perror("send");

		if ((fdFile = openFile("file400.html")) < 0) perror("Erreur open");

		while ((nbOctets = read(fdFile, buffer, 100)) > 0) {
			if (send(client_sockfd, buffer, nbOctets , 0) < 0) perror (" Erreur send ");
		}
    }
	else {
		if ((fdFile = openFile(fileName)) < 0) perror("Erreur open"); // TODO : make a 404 response process 
		else processResponse(fileName, client_sockfd, fdFile);
	}

	close(client_sockfd);

}


int processOpenError (int client_sockfd, int fdFile) {

    int nbOctets;
	char buffer[1000];

	if (errno == ENOENT) { // file doesn't exist

		if (send(client_sockfd, HEADER_404, sizeof(char) * strlen(HEADER_404) , 0) < 0) perror("Erreur send");
		if ((fdFile = openFile("file404.html")) < 0) perror("Erreur open");
		
		while ((nbOctets = read(fdFile, buffer, 100)) > 0) {
			if (send(client_sockfd, buffer, nbOctets , 0) < 0) perror(" Erreur send ");
		}
	} else if (errno == EACCES) { // file is not readable

		if (send(client_sockfd, HEADER_500, sizeof(char) * strlen(HEADER_500) , 0) < 0) perror("Erreur send");
		if ((fdFile = openFile("file500.html")) < 0) perror("Erreur open");
		
		while ((nbOctets = read(fdFile, buffer, 100)) > 0) {
			if (send(client_sockfd, buffer, nbOctets , 0) < 0) perror("Erreur send");
		}
	}

}