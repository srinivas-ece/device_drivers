#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    char buf[256];
    int ret;

    fd = open("/dev/ass2", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    printf("Reading from /dev/ass2 (WILL WAIT until both writers write)...\n");

    ret = read(fd, buf, sizeof(buf) - 1);
    if (ret < 0) {
        perror("read");
        return 1;
    }

    buf[ret] = '\0';
    printf("Combined message: %s\n", buf);

    close(fd);
    return 0;
}

