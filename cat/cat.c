#include "helpers.h"
#include <stdio.h>
#include <unistd.h>

const size_t SIZE_BUFFER = 1024;

int main() {
    char buf[SIZE_BUFFER];
    while (1) {
        size_t bytes = read_(STDIN_FILENO, buf, SIZE_BUFFER);
        if (bytes == 0)
            break;
        write_(STDOUT_FILENO, buf, bytes);
    }
    return 0;
}
