# HTTP

# Utils

GCC command: `gcc main.c src/http.c src/parser.c src/server.c -o main`

# Todo

- [ ] Split processRequest() into `getGETRequest()` and `processRequest()`
- [ ] `port` should be an int, and we could iterate over it if it's already in use (while binding it), then we convert it to char* to pass it to the bind() function #https://stackoverflow.com/questions/8257714/how-to-convert-an-int-to-string-in-c
- [ ] Log system
- [ ] Comments (and translate those in english in french)
- [ ] Factorize