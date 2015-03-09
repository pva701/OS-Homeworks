#include "helpers.h"
#include <unistd.h>
#include <cstdio.h>
const size_t MAX_LEN_WORDS = 4096 + 10;
const char DELIMITER = ' ';

void reverse(char* beg, char* end) {
    for (; beg < end; ++beg, --end) {
        char tmp = *beg;
        *beg = *end;
        *end = tmp;
    }
}

int main() {
    char word[MAX_LEN_WORDS];
    while (1) {
        size_t bytes = read_until(STDIN_FILENO, word, MAX_LEN_WORDS, DELIMITER);
        if (bytes == 0)
            break;
        if (word[bytes] == DELIMITER) {
            reverse(word, word + bytes - 1);
            write_(STDOUT_FILENO, word, bytes - 1);
            write_(STDOUT_FILENO, word + bytes, 1);
        } else {
            reverse(word, word + bytes);
            write_(STDOUT_FILENO, word, bytes);
        }
    }
    return 0;
}
