#include "helpers.h"
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

ssize_t read_(int fd, void *buf, size_t count) {
    ssize_t bytesRead = 0;
    while (bytesRead < count) {
        ssize_t actualRead = read(fd, buf + bytesRead, count - bytesRead);
        if (actualRead == 0 || actualRead == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
            break;
        else 
            bytesRead += actualRead;
    }
    return bytesRead;
}

ssize_t write_(int fd, void *buf, size_t count) {
    ssize_t bytesWritten = 0;
    while (bytesWritten < count) {
        ssize_t actualWritten = write(fd, buf + bytesWritten, count - bytesWritten);
        if (actualWritten == -1) {
            if (errno != EAGAIN && errno != EWOULDBLOCK)
                break;
        } else 
            bytesWritten += actualWritten;
    }
    return bytesWritten;
}    


#define MAX_SIZE 1024
struct CharQueue {
    char data[2 * MAX_SIZE];
    size_t l, r;
};
void ensure(struct CharQueue* q) {
    if (q->l + MAX_SIZE > 2 * MAX_SIZE) {
        size_t i = 0;
        for (; i < q->r - q->l; ++i)
            q->data[i] = q->data[i + q->l];
        q->r -= q->l;
        q->l = 0;
    }
}
size_t push(struct CharQueue* q, void* bufTo, size_t count, char delimiter) {
    size_t pushed = 0;
    char *bufToChr = (char*)bufTo;
    for (; pushed < count && q->data[q->l + pushed] != delimiter; ++pushed)
        bufToChr[pushed] = q->data[q->l + pushed];
    q->l += pushed;
    ensure(q);
    return pushed;
}
size_t size(struct CharQueue* q) {
    return q->r - q->l;
}

ssize_t read_until(int fd, void * buf, size_t count, char delimiter) {
    static struct CharQueue* q;
    if (q == NULL) {
        q = (struct CharQueue*)malloc(sizeof (struct CharQueue));
        q->l = 0;
        q->r = 0;
    }
    size_t ptr = 0;
    while (ptr < count) {
        size_t actualRead = -2;
        if (size(q) != MAX_SIZE)
            actualRead = read(fd, q->data + q->r, MAX_SIZE - size(q));
        if (actualRead == 0 || actualRead == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
            break;
        else {
            if (actualRead != -2) 
                q->r += actualRead;
            size_t mn = size(q) < count - ptr ? size(q) : count - ptr;
            size_t pushed = push(q, buf + ptr, mn, delimiter);
            ptr += pushed;
            if (size(q) != 0)
                break;
        }
    }
    return ptr;
}

