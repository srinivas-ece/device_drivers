#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd = open("/dev/sync", O_RDWR);
    if (fd < 0) {
        printf("Device open failed\n");
        return 1;
    }

    char data2[] = "CCCCCC";

    for (int i = 0; i < 100000; i++) {
        write(fd, data2, strlen(data2));
        usleep(10);
    }

    close(fd);
}
