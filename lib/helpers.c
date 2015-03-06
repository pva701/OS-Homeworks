#include "helpers.h"
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

ssize_t read_(int fd, void *buf, size_t count) {
    ssize_t bytesRead = 0;
    while (bytesRead < count) {
        ssize_t actualRead = read(fd, buf + bytesRead, count - bytesRead);
        if (actualRead == 0)
            break;
        else if (actualRead == -1) {
            if (errno != EAGAIN && errno != EWOULDBLOCK)
                break;
        } else 
            bytesRead += actualRead;
    }
    return bytesRead;
}

ssize_t write_(int fd, void *buf, size_t count) {
    ssize_t bytesWritten = 0;
    while (bytesWritten < count) {
        ssize_t actualWritten = read(fd, buf + bytesWritten, count - bytesWritten);
        if (actualWritten == -1) {
            if (errno != EAGAIN && errno != EWOULDBLOCK)
                break;
        } else 
            bytesWritten += actualWritten;
    }
    return bytesWritten;
}    
