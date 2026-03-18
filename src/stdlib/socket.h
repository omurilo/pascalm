#ifndef SOCKET_H
#define SOCKET_H

#include <netinet/in.h>

#ifndef PASCAL_STRING_DEFINED
#define PASCAL_STRING_DEFINED
typedef struct {
    unsigned int length;
    char *data;
} PascalString;
#endif

typedef struct {
    int fd;
    struct sockaddr_in address;
} Socket;

Socket socket_create();
int socket_bind(Socket *s, const char *ip, int port);
int socket_listen(Socket *s, int backlog);
int socket_accept(Socket *s, Socket *client);
int socket_connect(Socket *s, const char *ip, int port);
ssize_t socket_send(Socket *s, PascalString buf);
PascalString socket_recv(Socket *s, int maxlen);
int socket_close(Socket *s);

#endif