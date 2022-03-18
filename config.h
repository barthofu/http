#ifndef __CONFIG_H
#define __CONFIG_H

// server
#define LISTEN_PORT "2000"

// client (website)
#define BASE_WEBSITE_DIR "./website/"

// headers

    // 2xx
#define HEADER_HTML "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
#define HEADER_PNG "HTTP/1.1 200 OK\r\nContent-Type: image/png\r\n\r\n"
#define HEADER_JPG "HTTP/1.1 200 OK\r\nContent-Type: image/jpg\r\n\r\n"

    // 4xx
#define HEADER_400 "HTTP/1.1 400 BAD REQUEST\r\nContent-Type: text/html\r\n\r\n"
#define HEADER_404 "HTTP/1.1 404 FILE NOT FOUND\r\nContent-Type: text/html\r\n\r\n"

    // 5xx
#define HEADER_500 "HTTP/1.1 500 INTERNAL SERVER ERROR\r\nContent-Type: text/html\r\n\r\n"

#endif