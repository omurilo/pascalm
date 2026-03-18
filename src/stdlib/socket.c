#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>

Socket socket_create() {
    Socket s;
    s.fd = socket(AF_INET, SOCK_STREAM, 0);
    if (s.fd < 0) {
        perror("create socket");
        exit(1);
    }
    return s;
};

int socket_bind(Socket *s, const char *ip, int port) {
    int opt = 1;

    if (setsockopt(s->fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(1);
    }
    s->address.sin_family = AF_INET;
    s->address.sin_addr.s_addr = inet_addr(ip);
    s->address.sin_port = htons(port);

    if (bind(s->fd, (struct sockaddr*)&s->address,
             sizeof(s->address)) < 0) {
        perror("bind failed");
        exit(1);
    }

    return 0;
};

int socket_listen(Socket *s, int backlog) {
     if (listen(s->fd, backlog) < 0) {
        perror("listen failed");
        exit(1);
    }

    return 0;
};

int socket_accept(Socket *s, Socket *client) {
    socklen_t addrlen = sizeof(client->address);
    client->fd = accept(s->fd, (struct sockaddr*)&client->address, &addrlen);
    if (client->fd < 0) {
        perror("accept failed");
        exit(1);
    }
    return 0;
};

int socket_connect(Socket *s, const char *ip, int port) {
    s->address.sin_family = AF_INET;
    s->address.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &s->address.sin_addr) <= 0) {
        perror("Invalid address");
        exit(1);
    }
    if (connect(s->fd, (struct sockaddr*)&s->address, sizeof(s->address)) < 0) {
        perror("Connection failed");
        exit(1);
    }
    return 0;
};

ssize_t socket_send(Socket *s, PascalString buf) {
    ssize_t sent = send(s->fd, buf.data, buf.length, 0);
    if (sent < 0) {
        perror("send failed");
        exit(1);
    }
    return sent;
};

PascalString socket_recv(Socket *s, int maxlen) {
    PascalString result;
    result.data = (char *)malloc(maxlen + 1);
    if (!result.data) {
        perror("malloc failed");
        exit(1);
    }
    ssize_t received = recv(s->fd, result.data, maxlen, 0);
    if (received < 0) {
        perror("recv failed");
        free(result.data);
        result.data = NULL;
        result.length = 0;
        return result;
    }
    result.data[received] = '\0';
    result.length = (unsigned int)received;
    return result;
};

int socket_close(Socket *s) {
    if (close(s->fd) < 0) {
        perror("close failed");
        exit(1);
    }
    return 0;
};