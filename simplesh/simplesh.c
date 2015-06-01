#include "helpers.h"
#include "bufio.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
extern int resultFd;
#define MAX_BUF_SIZE 4096
char line[MAX_BUF_SIZE];
void dollar() {
    write(STDOUT_FILENO, "$ ", 3);
}

void sigHandler(int sig) {
    dollar();
}

int main() {
    signal(SIGINT, sigHandler);
    struct buf_t *buffer = buf_new(MAX_BUF_SIZE);
    dollar();
    while (1) {
        ssize_t bytes = buf_getline(STDIN_FILENO, buffer, line);
        if (bytes == 0)
             break;
        else if (bytes < 0)
            return -1;
        --bytes;
        int cntProgs = 0, i = 0, nonSpace = 0;
        for (; i < bytes; ++i) {
            cntProgs += line[i] == '|';
            nonSpace += line[i] != ' ';
        }
        if (nonSpace == 0) {
            dollar();
            continue;
        }
        ++cntProgs;

        struct execargs_t** progs = malloc(cntProgs*sizeof(struct execargs_t*));
        i = 0;
        cntProgs = 0;
        for (; i < bytes;) {
            int j = i;
            while (i < bytes && line[i] != '|') ++i;
            progs[cntProgs] = new_execargs_t_from_string(line + j, line + i);
            ++i;
            ++cntProgs;
        }
        int er = runpiped(progs, cntProgs);
/*        if (er == 0) {
            while (1) {
                bytes = read(resultFd, line, MAX_BUF_SIZE);
                if (bytes == 0) break;
                write(STDIN_FILENO, line, bytes);
            }
            close(resultFd);
        }*/
        dollar();
    }
    return 0;
}
