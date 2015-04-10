#include "helpers.h"
#include <stdio.h>
#include <unistd.h>

const size_t MAX_LEN_WORD = 4096;

int main(int argc, char* argv[]) {
    if (argc == 0)
        return 0;
    char word[MAX_LEN_WORD];
    char* *const newArgs = malloc(sizeof(char*) * (argc + 1));
    size_t i;
    for (i = 0; i < argc - 1; ++i)
        newArgs[i] = argv[i + 1];
    const char* file = newArgs[0];
    while (1) {
        ssize_t len = read_until(STDIN_FILENO, word, MAX_LEN_WORD, '\n');
        printf("len = %d\n", len);
        size_t last = len;
        if (len == 0 || len == -1)
            break;
        if (word[len - 1] == '\n') {
            word[len - 1] = 0;
            last--;
        } else 
            word[len] = 0;
        newArgs[argc - 1] = word;
        newArgs[argc] = NULL;
        int sp = spawn(file, newArgs);
        printf("sp = %d\n", sp);
        if (sp == 0) {
            word[last] = '\n';
            ssize_t er = write_(STDOUT_FILENO, word, last + 1);
            if (er == -1)
                break;
        }
    }
    free(newArgs);
    return 0;
}
