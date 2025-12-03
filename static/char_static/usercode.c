#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define DEVICE "/dev/srini"

int main()
{
    int fd;
    char write_buf[100] = "hii ra harshaaaaaaaaa!";
    char read_buf[100];

    // Open device
    fd = open(DEVICE, O_RDWR);
    if (fd < 0) {
        perror("Cannot open device");
        return -1;
    }

    printf("Device opened successfully.\n");

    // Write to device
    if (write(fd, write_buf, strlen(write_buf)) < 0) {
        perror("Write failed");
        close(fd);
        return -1;
    }
    printf("Written to device: %s\n", write_buf);

    // Read from device
    if (read(fd, read_buf, sizeof(read_buf)) < 0) {
        perror("Read failed");
        close(fd);
        return -1;
    }

    printf("Read from device: %s\n", read_buf);

    // Close device
    close(fd);
    printf("Device closed.\n");

    return 0;
}

