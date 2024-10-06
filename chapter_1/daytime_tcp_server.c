//
// Created by rudi on 10/5/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <netinet/in.h>
#include <sys/socket.h>

#define LISTENQ 8
#define MAXLINE 4096

void err_quit(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(-1);
}

int main(int argc, char *argv[]) {
    int listen_fd, conn_fd;
    struct sockaddr_in servaddr;
    char buffer[MAXLINE];
    time_t ticks;

    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        err_quit("socket error");
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(8080);

    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    listen(listen_fd, LISTENQ);

    for (;;) {
        conn_fd = accept(listen_fd, (struct sockaddr *) NULL, NULL);

        ticks = time(NULL);
        snprintf(buffer, sizeof(buffer), "%.24s\r\n", ctime(&ticks));
        write(conn_fd, buffer, strlen(buffer));

        close(conn_fd);
    }
}
