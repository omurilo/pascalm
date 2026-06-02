#ifndef HTTP_H
#define HTTP_H

#define MAX_HEADERS 32

#ifndef PASCAL_STRING_DEFINED
#define PASCAL_STRING_DEFINED
typedef struct {
    unsigned int length;
    char *data;
} PascalString;
#endif

/* Socket deve ser definido antes (socket.h emitido primeiro pelo compilador) */

typedef struct {
    char key[64];
    char value[256];
} HttpHeader;

typedef struct {
    char method[16];
    char path[256];
    char version[16];
    char host[256];
    HttpHeader *headers;
    int header_count;
    char *body;
} HttpRequest;

typedef struct {
    int status_code;
    char status_text[64];
    HttpHeader headers[MAX_HEADERS];
    char *body;
} HttpResponse;

int http_send_request(Socket *s, const char *method, const char *path, HttpHeader *headers, const char *body);
int http_read_response(Socket *s, char **buffer, size_t *buflen);
int http_read_request(Socket *s, HttpRequest *req);
int http_send_response(Socket *s, HttpResponse *res);

#endif