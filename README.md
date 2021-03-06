# HTTP

Serveur web réalisé dans le cadre du TP3 de Programmation Répartie à l'IUT Lyon 1 - site Doua par **Bartholomé GILI** et **Lazare CHEVEREAU** 
C'est un serveur très basique qui peut renvoyer des fichiers HTML, PNG et JPG situés dans le dossier `website` via des requêtes HTTP GET classiques.
Chaque connexion de clients est loggée dans le fichier `logs.txt`.

# Pré-requis

- `cmake`
- `make`

# Utilisation

1. `cmake CMakeLists.txt`
2. `make`
3. `./http`

# Configuration

Toute la configuration de l'application peut être retrouvée dans le fichier `config.h`. Sont ainsi modifiables :
- Le port
- Le fichier où seront stockés les logs
- Le chemin d'accès au répertoire contenant le site web statique

# Fonctionnalités

### 1. Serveur
- [x] Mise en place de la socket
- [x] Attente du client

### 2. Requête
- [x] Treshold d'au moins 1000 octets
- [x] Parser la requête

### 3. Réponse
- [x] On renvoie le fichier au client
- [x] Fermeture de la connexion

### 4. Bonus
- [x] `fork()` pour chacun des clients (permet les connexions simultanées)
- [x] Gestion des erreurs :
    - [x] 400
    - [x] 404
    - [x] 500
- [x] Gestion des images
    - [x] PNG
    - [x] JPG
- [x] Log de connexion (adresse IP + heure et date + URI) dans le fichier `logs.txt`
