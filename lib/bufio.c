#include "bufio.h"
#include <string.h>

#ifdef DEBUG
#define myAssert(x) if (!(x)) abort();
#else
#define myAssert(x)
#endif

struct buf_t *buf_new(size_t capacity) {
    struct buf_t* ret = (struct buf_t*)malloc(sizeof (struct buf_t));
    if (ret == NULL)
        return ret;
    ret->capacity = capacity;
    ret->size = 0;
    ret->data = (char*)malloc(sizeof(char) * capacity);
    if (ret->data == NULL) {
        free(ret);
        return NULL;
    }
    return ret;
}

void buf_free(struct buf_t* buf) {
    myAssert(buf != NULL);
    free(buf->data);
    free(buf);
}

size_t buf_capacity(struct buf_t* buf) {
    myAssert(buf != NULL);
    return buf->capacity;
}

size_t buf_size(struct buf_t* buf) {
    myAssert(buf != NULL);
    return buf->size;
}

ssize_t buf_fill(fd_t fd, struct buf_t *buf, size_t required) {
    myAssert(buf != NULL);
    myAssert(required <= buf->capacity);
    buf->size = 0;
    while (buf->size < required) {
        ssize_t bytes = read(fd, buf->data + buf->size, buf->capacity - buf->size);
        if (bytes == -1)
            return -1;
        if (bytes == 0)
            break;
        buf->size += bytes;
    }
    return buf->size;
}

ssize_t buf_flush(fd_t fd, struct buf_t *buf, size_t required) {
    myAssert(buf != NULL);
    size_t prevSize = buf->size;
    while (prevSize - buf->size < required && buf->size != 0) {
        ssize_t bytes = write(fd, buf->data, buf->size);
        if (bytes == -1)
            return -1;
        if (bytes == 0)
            break;
        buf->size -= bytes;
        memmove(buf->data, buf->data + bytes, buf->size);
    }
    return prevSize - buf->size;
}

