#include "helpers.h"
#include <stdio.h>
#include <unistd.h>

const int SIZE_BUFFER = 1000;

int main() {
    char buf[SIZE_BUFFER];
    while (1) {
        int bytes = read_(STDIN_FILENO, buf, SIZE_BUFFER);
        if (bytes == 0)
            break;
        write_(STDOUT_FILENO, buf, bytes);
    }
    return 0;
}
