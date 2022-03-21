#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#include "../../config.h"
#include "../utils/string.h"

// Cette fonction permet d'ouuvrir un fichier en y rajoutant BASE_WEBSITE_DIR avant le nom du fichier
int openFile (char* fileName) {

    int fdFile;
    
    if ((fdFile = open(concat(BASE_WEBSITE_DIR, fileName), O_RDONLY)) < 0) {
        perror("Erreur open");
        return -1;
    }
    
    return fdFile;
}