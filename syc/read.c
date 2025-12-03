#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd = open("/dev/sync", O_RDONLY);
    if (fd < 0) {
        printf("Device open failed!\n");
        return 1;
    }

    char buf[200];

    int ret = read(fd, buf, sizeof(buf) - 1);

    if (ret < 0) {
        printf("Read failed\n");
        return 1;
    }

    buf[ret] = '\0';   

    printf("BUFFER = %s\n", buf);

    close(fd);
    return 0;
}
