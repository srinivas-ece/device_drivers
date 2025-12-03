#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

#include "sriiotl.h"

int main() {
    int fd;
     
    char write_buf[BUF_LEN];
    char read_buf[BUF_LEN];

    printf("enter the str : ");
    fgets(write_buf,strlen(write_buf),stdin);

    fd = open("/dev/sri_iotl", O_RDWR);
    if (fd < 0) {
        perror("open");
        return -1;
    }


    write(fd, write_buf, sizeof(write_buf));


    read(fd, read_buf, BUF_LEN);
    printf("read from device : %s\n", read_buf);


    char ioctl_write_buf[BUF_LEN] = "mess to ioctl";  
    char ioctl_read_buf[BUF_LEN];                    
    ioctl(fd, CMD_TO_MGS, ioctl_write_buf);

    ioctl(fd, CMD_SET_MGS, ioctl_read_buf);
    printf("ioctl_read : %s\n", ioctl_read_buf);

    close(fd);
    return 0;
}

