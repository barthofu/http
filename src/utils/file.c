#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#include "../../config.h"

int openFile (char* fileName) {

    int fdFile;
    
    if ((fdFile = open(strcat(BASE_WEBSITE_DIR, fileName), O_RDONLY)) < 0) {
        perror("Erreur open");
        return -1;
    }
    
    return fdFile;
}