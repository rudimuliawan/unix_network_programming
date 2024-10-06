#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#define MAXLINE 4096

void err_quit(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(-1);
}

int main(int argc, char *argv[]) {
    int sock_fd, n;
    char recvline[MAXLINE+1];
    struct sockaddr_in serveaddr;

    if (argc != 2) {
        err_quit("invalid argc's argument");
    }

    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        err_quit("socket error");
    }

    bzero(&serveaddr, sizeof(serveaddr));
    serveaddr.sin_family = AF_INET;
    serveaddr.sin_port = htons(8080);

    if (inet_pton(AF_INET, argv[1], &serveaddr.sin_addr) <= 0) {
        err_quit("inet pton error for");
    }

    if (connect(sock_fd, (struct sockaddr *) &serveaddr, sizeof(serveaddr))) {
        err_quit("connect error");
    }

    while ((n = read(sock_fd, recvline, MAXLINE)) > 0) {
        recvline[n] = 0;
        if (fputs(recvline, stdout) == EOF) {
            err_quit("fputs error");
        }
    }

    if (n < 0) {
        err_quit("read error");
    }

    return 0;
}
