#include "bufio.h"
#include <assert.h>
#include <string.h>

struct buf_t *buf_new(size_t capacity) {
    struct buf_t* ret = (struct buf_t*)malloc(sizeof (struct buf_t));
    ret->capacity = capacity;
    ret->size = 0;
    ret->data = (char*)malloc(sizeof(char) * capacity);
    return ret;
}

void buf_free(struct buf_t* buf) {
    free(buf->data);
    free(buf);
}

size_t buf_capacity(struct buf_t* buf) {
    return buf->capacity;
}

size_t buf_size(struct buf_t* buf) {
    return buf->size;
}

ssize_t buf_fill(fd_t fd, struct buf_t *buf, size_t required) {
    assert(buf != NULL);
    assert(required <= buf->capacity);
    while (buf->size < required) {
        ssize_t bytes = read(fd, buf->data + buf->size, buf->capacity - buf->size);
        if (bytes == -1)
            return -1;
        buf->size += bytes;
    }
    return buf->size;
}

ssize_t buf_flush(fd_t fd, struct buf_t *buf, size_t required) {
    assert(buf != NULL);
    assert(buf->size >= required);
    size_t prevSize = buf->size;
    while (prevSize - buf->size < required) {
        ssize_t bytes = write(fd, buf->data, buf->size);
        if (bytes == -1)
            return -1;
        buf->size -= bytes;
        memmove(buf->data, buf->data + bytes, buf->size);
    }
    return prevSize - buf->size;
}

