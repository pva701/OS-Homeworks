#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "bufio.h"
#include <string.h>
#include <fcntl.h>

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
int main(int argc, const char* argv[]) {
    if (argc != 3) {
        printf("Input 3 agruments!\n");
        return 0;
    }

    struct buf_t *buf = buf_new(MAX_SIZE_BUFFER);
    int port = atoi(argv[1]);
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
            int fileFd = open(fileName, O_RDONLY);
            while (1) {
                ssize_t rb = buf_fill(fileFd, buf, MAX_SIZE_BUFFER);
                if (rb <= 0) break;
                buf_flush(fd, buf, MAX_SIZE_BUFFER);
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
