#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) { perror("socket"); return 1; }

    // Allow quick port reuse after killing server
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind"); return 1;
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen"); return 1;
    }

    printf("Listening on port %d... (blocking until someone connects)\n", PORT);
    
    struct sockaddr_in client_addr;
    socklen_t addrlen = sizeof(client_addr);
    int new_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addrlen);
    if (new_socket < 0) { perror("accept"); return 1; }

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
    printf("Connection accepted from %s\n", client_ip);

    char buffer[1024] = {0};
    read(new_socket, buffer, sizeof(buffer));
    printf("Received message: '%s'\n", buffer);

    close(new_socket);
    close(server_fd);
    return 0;
}
