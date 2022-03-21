# HTTP

Serveur web réalisé dans le cadre du TP3 de Programmation Répartie à l'IUT Lyon 1 - site Doua. 
C'est un serveur très basique qui peut renvoyer des fichiers HTML, PNG et JPG situés dans le dossier `website` via des requêtes HTTP GET classiques.

# Pré-requis

- `cmake`
- `make`

# Utilisation

1. `cmake CMakeLists.txt`
2. `make`
3. `./http`

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
- [x] Log de connexion (adresse IP + heure et date + URI)