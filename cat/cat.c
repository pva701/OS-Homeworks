#include "helpers.h"
#include <stdio.h>
#include <unistd.h>

const size_t SIZE_BUFFER = 1024;
//Yan privet!
int main() {
    char buf[SIZE_BUFFER];
    while (1) {
        ssize_t bytes = read_(STDIN_FILENO, buf, SIZE_BUFFER);
        if (bytes == 0 || bytes == -1)
            break;
        bytes = write_(STDOUT_FILENO, buf, bytes);
        if (bytes == -1)
            break;
    }
    return 0;
}
