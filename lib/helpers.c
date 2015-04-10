#include "helpers.h"
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

ssize_t read_(int fd, void *buf, size_t count) {
    ssize_t bytesRead = 0;
    while (bytesRead < count) {
        ssize_t actualRead = read(fd, buf + bytesRead, count - bytesRead);
        if (actualRead == 0)
            break;
        if (actualRead == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
            return -1;
        else if (actualRead != -1)
            bytesRead += actualRead;
    }
    return bytesRead;
}

ssize_t write_(int fd, void *buf, size_t count) {
    ssize_t bytesWritten = 0;
    while (bytesWritten < count) {
        ssize_t actualWritten = write(fd, buf + bytesWritten, count - bytesWritten);
        if (actualWritten == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
            return -1;
        else if (actualWritten != -1)
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
    if (count == 0) 
        return 0;
    size_t pushed = 0;
    char *bufToChr = (char*)bufTo;
    for (;pushed < count && q->data[q->l + pushed] != delimiter; ++pushed)
        bufToChr[pushed] = q->data[q->l + pushed];
    if (pushed < count) {
        bufToChr[pushed] = q->data[q->l + pushed];
        ++pushed;
    }
    q->l += pushed;
    ensure(q);
    return pushed;
}
size_t size(struct CharQueue* q) {
    return q->r - q->l;
}

ssize_t read_until(int fd, void * buf, size_t count, char delimiter) {
    if (count == 0)
        return 0;
    static struct CharQueue* q;
    if (q == NULL) {
        q = malloc(sizeof (struct CharQueue));
        q->l = 0;
        q->r = 0;
    }
    size_t ptr = 0;
    int hasDelimiter = 0;
    char *bufToChr = (char*)buf;
    if (size(q) > 0) {
        size_t mn = size(q) < count - ptr ? size(q) : count - ptr;
        size_t pushed = push(q, buf + ptr, mn, delimiter);
        ptr += pushed;
        if (bufToChr[ptr - 1] == delimiter) hasDelimiter = 1;
    }

    while (ptr < count && !hasDelimiter) {
        size_t actualRead = -2;
        if (size(q) != MAX_SIZE) 
            actualRead = read(fd, q->data + q->r, MAX_SIZE - size(q));
        if (actualRead > 0)
            q->r += actualRead;
        if (actualRead == 0 || actualRead == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
            break;
        if (size(q) > 0) {
            size_t mn = size(q) < count - ptr ? size(q) : count - ptr;
            size_t pushed = push(q, buf + ptr, mn, delimiter);
            ptr += pushed;
            if (bufToChr[ptr - 1] == delimiter) hasDelimiter = 1;
        }
    }
    return ptr;
}

int spawn(const char * file, char * const argv []) {
    int proc = fork();
    if (proc != 0) {//in parent process
        int res;
        waitpid(proc, &res, 0);
        return res;
    } else {//in child process
        int fd = open("/dev/null",  O_WRONLY);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        close(fd);
        return execvp(file, argv);
    }
}
