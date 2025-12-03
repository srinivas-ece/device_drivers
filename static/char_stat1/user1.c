#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(){
	int fd;
	 char read_buf[100];
	 char write_buf[100] = "hii ra harshaaaaaaaaa!";
	fd=open("/dev/sri",O_RDWR,0666);
	write(fd, write_buf, strlen(write_buf));

	read(fd, read_buf, sizeof(read_buf));
	printf("Read from device: %s\n", read_buf);
	//write(fd, write_buf, strlen(write_buf));
	
	printf("Written to device: %s\n", write_buf);
	close(fd);
	return 0;
}

