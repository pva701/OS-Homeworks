#include "helpers.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
const size_t MAX_LEN_WORD = 4096 + 10;
const char DELIMITER = ' ';

int main() {
    char word[MAX_LEN_WORD];
    while (1) {
        ssize_t bytes;
        bytes = read_until(STDIN_FILENO, word, MAX_LEN_WORD, DELIMITER);
        if (bytes == 0 || bytes == -1)
            break;
        if (word[bytes - 1] == DELIMITER) 
            --bytes;
        char num[11];
        sprintf(num, "%d\n", bytes);
        bytes = write_(STDOUT_FILENO, num, strlen(num));
        if (bytes == -1)
            break;
    }
    return 0;
}
