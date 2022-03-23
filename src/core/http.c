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
#include "../utils/logger.h" 
#include "../constants/headers.h"

int sendResponse (int client_sockfd, char *header, int fdFile) {

	char buffer[1000];
	int nbOctets;

	// Envoie du header
	if (send(client_sockfd, header, strlen(header), 0) < 0) perror("send");

	// Envoie du contenu du fichier, tant que le fichier n'est pas fini
	while ((nbOctets = read(fdFile, buffer, 100)) > 0) {
		if (send(client_sockfd, buffer, nbOctets, 0) < 0) perror("send");
	}

	close(fdFile);
	return 0;
}


int processResponse (char *fileName, int client_sockfd, int fdFile) {

	// On adapte le header que l'on va renvoyer en fonction du format de fichier demandé
	if (strstr(fileName, ".html")) sendResponse(client_sockfd, HEADER_HTML, fdFile);
	else if (strstr(fileName, ".png")) sendResponse(client_sockfd, HEADER_PNG, fdFile);
	else if (strstr(fileName, ".jpg")) sendResponse(client_sockfd, HEADER_JPG, fdFile);
	else {
		fprintf(stderr, "Erreur processResponse(): le fichier %s n'est pas reconnu\n", fileName);
		return -1;
	}
}


int processOpenError (int client_sockfd, int fdFile) {

    int nbOctets;
	char buffer[1000];

	if (errno == ENOENT) { // Le fichier n'existe pas
 
		if ((fdFile = openFile("file404.html")) < 0) perror("Erreur open");
		sendResponse(client_sockfd, HEADER_404, fdFile);
		
	} else if (errno == EACCES) { // Le fichier n'est pas lisible par le serveur

		if ((fdFile = openFile("file500.html")) < 0) perror("Erreur open");
		sendResponse(client_sockfd, HEADER_500, fdFile);
	}
}


int processRequest (int client_sockfd, struct sockaddr_storage client_addr) {

    int nbOctets, fdFile;
    char buffer[1000], fileName[1000];

    // Récupération de la requête depuis le kernel via l'appel système recv()
    if (recv(client_sockfd, buffer, sizeof(buffer) * sizeof(char), 0) < 0) perror("recv");

    // On parse la requête afin d'y en extraire le nom du fichier demandé
    if (parseRequest(buffer, sizeof(buffer), fileName, sizeof(fileName)) == -1) {
        
        // Si la requête est invalide, on renvoie une erreur 400
		if ((fdFile = openFile("file400.html")) < 0) perror("Erreur open");
		sendResponse(client_sockfd, HEADER_400, fdFile);
    
	} else {

		// Au contraire, si la requête est valide :
			
			// 1. On la log dans un journal
		logConnection(client_addr, fileName);

			// 2. On ouvre le fichier demandé
		if ((fdFile = openFile(fileName)) < 0) {

			// Si l'ouverture du fichier échoue, on renvoie une erreur
			processOpenError(client_sockfd, fdFile); 	
		}
		else {
			
			// 3. On envoie le fichier au client
			processResponse(fileName, client_sockfd, fdFile);
		}
	}

	close(client_sockfd);

}