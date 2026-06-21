#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define PORT1 80
#define PORT2 443

int create_listener(int port) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) { perror("socket"); exit(1); }

    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind"); exit(1);
    }
    if (listen(fd, 3) < 0) {
        perror("listen"); exit(1);
    }
    return fd;
}

int main() {
    int fd1 = create_listener(PORT1);
    int fd2 = create_listener(PORT2);

    printf("Listening on port %d (descriptor %d) and port %d (descriptor %d)...\n", PORT1, fd1, PORT2, fd2);

    fd_set readfds;
    while (1) {
        FD_ZERO(&readfds);
        FD_SET(fd1, &readfds);
        FD_SET(fd2, &readfds);
        
        int max_fd = (fd1 > fd2) ? fd1 : fd2;

        int activity = select(max_fd + 1, &readfds, NULL, NULL, NULL);
        if (activity < 0) { perror("select"); break; }

        if (FD_ISSET(fd1, &readfds)) {
            int client = accept(fd1, NULL, NULL);
            printf("Connection received on Port %d (HTTP desk)!\n", PORT1);
            write(client, "HTTP Hello!\n", 12);
            close(client);
        }
        if (FD_ISSET(fd2, &readfds)) {
            int client = accept(fd2, NULL, NULL);
            printf("Connection received on Port %d (HTTPS desk)!\n", PORT2);
            write(client, "HTTPS Hello!\n", 13);
            close(client);
        }
    }

    close(fd1);
    close(fd2);
    return 0;
}
