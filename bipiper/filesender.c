#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "bufio.h"
#include <string.h>

int startServer(int port) {
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1)
        return -1;
	int one = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int)) == -1)
        return -1;
	struct sockaddr_in addr = {
		.sin_family = AF_INET,
		.sin_port = htons(port), 
		.sin_addr = {.s_addr = INADDR_ANY}};
	if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1)
        return -1;
	if (listen(sock, 1) == -1)
        return -1;
    return sock;
}

#define MAX_SIZE_BUFFER 4096
int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Input 3 agruments!\n");
        return 0;
    }
    int fd = open(argv[2]);
    printf("fd = %d\n", fd);
    perror("msg");
    close(fd);
    return 0;
/*    struct buf_t *buf = buf_new(MAX_SIZE_BUFFER);
    int n = strlen(fileName);
    char *tmp = malloc(strlen(fileName) + 3);
    int i = 0;
    for (; i <= n; ++i) tmp[i + 2] = fileName[i];
    tmp[0] = '.';
    tmp[1] = '/';
    fileName = tmp;
    printf("s = %s\n", fileName);*/
    int port = itoa(argv[1]);
    const char* fileName = argv[2];
    int sock = startServer(port);
	printf("sock = %d\n", sock);
    while (1) {
    	struct sockaddr_in client;
    	socklen_t sz = sizeof(client);
    	int fd = accept(sock, (struct sockaddr*)&client, &sz);
        printf("ac = %d\n", fd);
	    if (fd == -1) {
		    perror("accept");
            continue;
        }
        printf("accept = %d\n", fd);
        printf("from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        int proc = fork();
        if (proc == 0) {//in child
            printf("name = %s\n", fileName);
            int fileFd = open(fileName);
            perror("error");
            printf("file fd = %d\n", fileFd);
            char b[1000];
            while (1) {
                ssize_t bytes = read(fileFd, b, 1000);
                printf("bytes = %d\n", bytes);
                perror("nooooooo");
                if (bytes <= 0) break;
                ssize_t wr = write(fd, b, 1000);
                printf("wr = %d\n", wr);

/*                ssize_t rb = buf_fill(fileFd, buf, MAX_SIZE_BUFFER);
                printf("rb = %d\n", rb);
                if (rb <= 0) break;
                buf_flush(fd, buf, MAX_SIZE_BUFFER);*/
            }
            close(fileFd);
            close(fd);
            break;
        } else close(fd);
        wait(proc);
    }
    close(sock);
    return 0;
}
