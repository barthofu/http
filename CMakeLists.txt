# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.0)

# Notre projet est étiqueté http
project(http)

# Crée des variables avec les fichiers à compiler
set(SRCS
    main.c
    src/core/http.c
    src/core/server.c
    src/utils/parser.c
    src/utils/file.c
    src/utils/string.c
    )
    
set(HEADERS
    src/core/http.h
    src/core/server.h
    src/utils/parser.h
    src/utils/file.h
    src/utils/string.h
    config.h
    )

# On indique que l'on veut un exécutable "http" compilé à partir des fichiers décrits par les variables SRCS et HEADERS
add_executable(http ${SRCS} ${HEADERS})