#include "helpers.h"
#include <stdio.h>
#include <unistd.h>

const size_t SIZE_BUFFER = 1024;
//Yan privet!
int main() {
    char buf[SIZE_BUFFER];
    while (1) {
        ssize_t bytes = read_(STDIN_FILENO, buf, SIZE_BUFFER);
        if (bytes == 0)
            break;
        if (bytes == -1) {
            write_(STDERR_FILENO, "error", 5);
            return -1;
        }
        bytes = write_(STDOUT_FILENO, buf, bytes);
        if (bytes == -1)
            return -1;
    }
    return 0;
}
