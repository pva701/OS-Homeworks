#include "helpers.h"
#include <stdio.h>
#include <unistd.h>

const size_t SIZE_BUFFER = 1024;

int main() {
    char buf[SIZE_BUFFER];
    while (1) {
        ssize_t bytes = read_(STDIN_FILENO, buf, SIZE_BUFFER);
        if (bytes == 0)
            break;
        if (bytes == -1) {
            fprintf(stderr, "error");
            return 0;
        }
        write_(STDOUT_FILENO, buf, bytes);
    }
    return 0;
}
