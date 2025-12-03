#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

#include "sriioctl.h"

int main() {
    int fd;
    fd = open("/dev/sri_iotl", O_RDWR);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    // Buffer for normal read/write
    char write_buf[BUF_LEN] = "srinivas hii raa mawa";
    char read_buf[BUF_LEN];

    // Write to device
    write(fd, write_buf, strlen(write_buf) + 1);

    // Read from device
    read(fd, read_buf, BUF_LEN);
    printf("read from device : %s\n", read_buf);

    // IOCTL section
    char ioctl_write_buf[BUF_LEN] = "mess to ioctl";  // send to kernel
    char ioctl_read_buf[BUF_LEN];                     // receive from kernel

    ioctl(fd, CMD_TO_MGS, ioctl_write_buf);

    ioctl(fd, CMD_SET_MGS, ioctl_read_buf);
    printf("ioctl_read : %s\n", ioctl_read_buf);

    close(fd);
    return 0;
}

