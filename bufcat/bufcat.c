#include "bufio.h"
#include <stdio.h>
#include <unistd.h>
const size_t SIZE_BUFFER = 4096;
int main() {
    struct buf_t *buf = buf_new(SIZE_BUFFER);
    while (1) {
        ssize_t bytes = buf_fill(STDIN_FILENO, buf, 1);
        if (bytes == -1) return -1;
        if (bytes == 0) break;
        size_t sz = buf_size(buf);
        bytes = buf_flush(STDOUT_FILENO, buf, sz);
        if (bytes == -1) return -1;
        if (bytes < sz) break;
    }
    buf_free(buf);
    return 0;
}
