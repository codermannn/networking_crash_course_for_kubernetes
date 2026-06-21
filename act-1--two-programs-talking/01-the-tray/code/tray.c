#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FIFO_PATH "/tmp/my_tray"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [write/read] [message]\n", argv[0]);
        return 1;
    }

    char *mode = argv[1];

    if (mode[0] == 'w') {
        char *msg = argv[2] ? argv[2] : "Hello from the tray!";
        printf("Opening tray for writing... (blocking until someone reads)\n");
        int fd = open(FIFO_PATH, O_WRONLY);
        if (fd < 0) { perror("open"); return 1; }
        printf("Writing message: '%s'\n", msg);
        write(fd, msg, 20);
        close(fd);
    } else {
        char buf[128] = {0};
        printf("Opening tray for reading... (blocking until someone writes)\n");
        int fd = open(FIFO_PATH, O_RDONLY);
        if (fd < 0) { perror("open"); return 1; }
        read(fd, buf, sizeof(buf));
        printf("Received message: '%s'\n", buf);
        close(fd);
    }

    return 0;
}
