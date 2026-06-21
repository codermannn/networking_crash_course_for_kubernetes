#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [IPAddress] [Message]\n", argv[0]);
        return 1;
    }

    char *ip = argv[1];
    char *msg = argv[2] ? argv[2] : "Hello from client socket!";

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) { perror("socket"); return 1; }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        perror("inet_pton"); return 1;
    }

    printf("Connecting to %s:%d... (blocking)\n", ip, PORT);
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect"); return 1;
    }

    printf("Sending message: '%s'\n", msg);
    send(sock, msg, strlen(msg), 0);

    close(sock);
    return 0;
}
