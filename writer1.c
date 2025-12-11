#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    char buf[128];

    fd = open("/dev/ass1", O_WRONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    printf("Enter message for device 1: ");
    scanf(" %[^\n]", buf);

    write(fd, buf, strlen(buf));
    printf("Written to /dev/ass1\n");

    close(fd);
    return 0;
}

