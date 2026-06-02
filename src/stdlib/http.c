#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
/* socket.h and http.h are emitted before this file by the PascalM compiler */

static int append_formatted(char *buffer, size_t buffer_size, size_t *offset, const char *format, ...) {
    if (*offset >= buffer_size) return -1;

    va_list args;
    va_start(args, format);
    int written = vsnprintf(buffer + *offset, buffer_size - *offset, format, args);
    va_end(args);

    if (written < 0 || (size_t)written >= (buffer_size - *offset)) {
        return -1;
    }

    *offset += (size_t)written;
    return 0;
}

int http_send_request(Socket *s, const char *method, const char *path, HttpHeader *headers, const char *body) {
    size_t body_len = body ? strlen(body) : 0;
    size_t req_size = 1024 + (MAX_HEADERS * 300) + body_len;
    char *request = malloc(req_size);
    if (!request) return -1;
    size_t offset = 0;
    if (append_formatted(request, req_size, &offset, "%s %s HTTP/1.1\r\n", method, path) < 0) {
        free(request);
        return -1;
    }
    for (int i = 0; i < MAX_HEADERS; i++) {
        if (headers[i].key[0] == '\0') break;
        if (append_formatted(request, req_size, &offset, "%s: %s\r\n", headers[i].key, headers[i].value) < 0) {
            free(request);
            return -1;
        }
    }
    if (append_formatted(request, req_size, &offset, "Content-Length: %zu\r\n\r\n", body_len) < 0) {
        free(request);
        return -1;
    }
    if (body && body_len > 0) {
        if (offset + body_len > req_size) {
            free(request);
            return -1;
        }
        memcpy(request + offset, body, body_len);
        offset += body_len;
    }
    PascalString ps;
    ps.data = request;
    ps.length = (unsigned int)offset;
    int sent = socket_send(s, ps);
    free(request);
    return sent;
}

int http_read_response(Socket *s, char **buffer, size_t *buflen) {
    size_t alloc_size = 4096;
    *buffer = malloc(alloc_size);
    if (!*buffer) return -1;
    PascalString ps = socket_recv(s, (int)(alloc_size - 1));
    if (!ps.data) return -1;
    *buffer = ps.data;
    *buflen = ps.length;
    return 0;
}

int http_read_request(Socket *s, HttpRequest *req) {
    char *buffer = NULL;
    size_t buflen = 0;
    if (http_read_response(s, &buffer, &buflen) < 0) {
        return -1;
    }

    char *saveptr;
    char *line = strtok_r(buffer, "\r\n", &saveptr);
    if (!line) { free(buffer); return -1; }
    sscanf(line, "%15s %255s %15s", req->method, req->path, req->version);

    req->headers = malloc(sizeof(HttpHeader) * MAX_HEADERS);
    req->header_count = 0;
    while ((line = strtok_r(NULL, "\r\n", &saveptr)) && line[0] != '\0') {
        if (req->header_count < MAX_HEADERS) {
            sscanf(line, "%63[^:]: %255[^\"]", req->headers[req->header_count].key, req->headers[req->header_count].value);
            req->header_count++;
        }
    }

    char *body_start = strstr(buffer, "\r\n\r\n");
    if (body_start) {
        body_start += 4;
        req->body = malloc(strlen(body_start) + 1);
        strcpy(req->body, body_start);
    } else {
        req->body = NULL;
    }

    req->host[0] = '\0';
    for (int i = 0; i < req->header_count; i++) {
        if (strcmp(req->headers[i].key, "Host") == 0) {
            strncpy(req->host, req->headers[i].value, sizeof(req->host)-1);
            req->host[sizeof(req->host)-1] = '\0';
            break;
        }
    }
    free(buffer);
    return 0;
}

int http_send_response(Socket *s, HttpResponse *res) {
    size_t body_len = res->body ? strlen(res->body) : 0;
    size_t resp_size = 1024 + (MAX_HEADERS * 300) + body_len;
    char *response = malloc(resp_size);
    if (!response) return -1;
    size_t offset = 0;
    if (append_formatted(response, resp_size, &offset, "HTTP/1.1 %d %s\r\n", res->status_code, res->status_text) < 0) {
        free(response);
        return -1;
    }
    for (int i = 0; i < MAX_HEADERS; i++) {
        if (res->headers[i].key[0] == '\0') break;
        if (append_formatted(response, resp_size, &offset, "%s: %s\r\n", res->headers[i].key, res->headers[i].value) < 0) {
            free(response);
            return -1;
        }
    }
    if (append_formatted(response, resp_size, &offset, "Content-Length: %zu\r\n\r\n", body_len) < 0) {
        free(response);
        return -1;
    }
    if (res->body && body_len > 0) {
        if (offset + body_len > resp_size) {
            free(response);
            return -1;
        }
        memcpy(response + offset, res->body, body_len);
        offset += body_len;
    }
    PascalString ps2;
    ps2.data = response;
    ps2.length = (unsigned int)offset;
    int sent = socket_send(s, ps2);
    free(response);
    return sent;
}