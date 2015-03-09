#include "helpers.h"
#include <unistd.h>
#include <stdio.h>
const size_t MAX_LEN_WORD = 4096 + 10;
const char DELIMITER = ' ';

void reverse(char* beg, char* end) {
    --end;
    for (; beg < end; ++beg, --end) {
        char tmp = *beg;
        *beg = *end;
        *end = tmp;
    }
}

int main() {
    char word[MAX_LEN_WORD];
    while (1) {
        size_t bytes = read_until(STDIN_FILENO, word, MAX_LEN_WORD, DELIMITER);
        if (bytes == 0)
            break;
        if (word[bytes - 1] == DELIMITER) {
            reverse(word, word + bytes - 1);
            write_(STDOUT_FILENO, word, bytes - 1);
            write_(STDOUT_FILENO, word + bytes - 1, 1);
        } else {
            reverse(word, word + bytes);
            write_(STDOUT_FILENO, word, bytes);
        }
    }
    return 0;
}
