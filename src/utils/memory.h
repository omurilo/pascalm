#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>
#include <stdio.h>

static size_t allocation_count = 0;

static inline void *xalloc(size_t n, size_t size) {
    void *ptr = calloc(n, size);
    if (!ptr) {
        fprintf(stderr, "❌ Out of memory at %s:%d\n", __FILE__, __LINE__);
        exit(1);
    }
    return ptr;
}

#define xcalloc(n, size) \
    ((type *)xalloc(n, sizeof(type)))

#define xnew(type) \
    ((type *)xalloc(1, sizeof(type)))

#endif
