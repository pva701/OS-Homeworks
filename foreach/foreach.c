#include "helpers.h"
#include <stdio.h>
#include <unistd.h>
#include <bufio.h>
#define MAX_LEN_WORD 4097
const size_t MAX_BUF_SIZE = MAX_LEN_WORD  + 1;

int main(int argc, char* argv[]) {
    if (argc == 0)
        return 0;
    char word[MAX_LEN_WORD + 1] = {0};
    char* *const newArgs = malloc(sizeof(char*) * (argc + 1));
    size_t i;
    for (i = 0; i < argc - 1; ++i)
        newArgs[i] = argv[i + 1];
    const char* file = newArgs[0];
    struct buf_t *buf = buf_new(MAX_BUF_SIZE);
    while (1) {
        ssize_t len = buf_getline(STDIN_FILENO, buf, word);
        int i = 0;
        if (len == -1 || len == 0)
            break;
        if (len % 2 == 0)
            continue;
        word[len] = 0;
        newArgs[argc - 1] = word;
        newArgs[argc] = NULL;
        int sp = spawn(file, newArgs);
        if (sp == 0) {
            word[len] = '\n';
            ssize_t er = write_(STDOUT_FILENO, word, len + 1);
            if (er == -1)
                break;
        }
    }
    free(newArgs);
    buf_free(buf);
    return 0;
}
