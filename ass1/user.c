#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int fd;
    char buff[100];
    int choice;

    fd = open("/dev/sri_u", O_RDWR);
    if (fd < 0) {
        printf("Error opening device!\n");
        return -1;
    }

    while (1) {
		
        printf("\n1. Write\n2. Read\n0. Exit\nEnter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {

        case 1:
            printf("Enter the string: ");
            fgets(buff, sizeof(buff), stdin);
			
			buff[strcspn(buff, "\n")] = '0';

            write(fd, buff, strlen(buff));
            printf("Data written to driver.\n");
            break;

        case 2:
            memset(buff, 0, sizeof(buff));
            read(fd, buff, sizeof(buff));
            printf("Data from driver: %s\n", buff);
            break;

        case 0:
            close(fd);
            printf("Exiting...\n");
            exit(0);

        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
