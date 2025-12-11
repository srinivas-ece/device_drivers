#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    char buf[128];

    fd = open("/dev/ass0", O_WRONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    printf("Enter message for device 0: ");
    scanf(" %[^\n]", buf);

    write(fd, buf, strlen(buf));
    printf("Written to /dev/ass0\n");

    close(fd);
    return 0;
}

