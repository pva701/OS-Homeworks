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
char q[2 * MAX_SIZE];
size_t l, r;
void ensure() {
    if (l + MAX_SIZE > 2 * MAX_SIZE) {
        size_t i = 0;
        for (; i < r - l; ++i)
            q[i] = q[i + l];
        r -= l;
        l = 0;
    }
}
size_t push(void* bufTo, size_t count, char delimiter) {
    size_t pushed = 0;
    char *bufToChr = (char*)bufTo;
    for (; pushed < count && q[l + pushed] != delimiter; ++pushed)
        bufToChr[pushed] = q[l + pushed];
    l += pushed;
    ensure();
    return pushed;
}
size_t size() {
    return r - l;
}

ssize_t read_until(int fd, void * buf, size_t count, char delimiter) {
    size_t ptr = 0;
    while (ptr < count) {
        size_t actualRead = -2;
        if (size() != MAX_SIZE)
            actualRead = read(fd, q + r, MAX_SIZE - size());
        if (actualRead == 0 || actualRead == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
            break;
        else {
            if (actualRead != -2) 
                r += actualRead;
            size_t mn = size() < count - ptr ? size() : count - ptr;
            size_t pushed = push(buf + ptr, mn, delimiter);
            ptr += pushed;
            if (size() != 0)
                break;
        }
    }
    return ptr;
}

