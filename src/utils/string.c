#include <stdlib.h>
#include <string.h>

// Fonction utilitaire afin de concatener deux chaines de caractères 
char* concat(const char *s1, const char *s2) 
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    
    return result;
}