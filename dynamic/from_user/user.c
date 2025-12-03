#include<fcntl.h>
#include<stdio.h>
#include <unistd.h>
#include<string.h>

int main ()
{
	int fd;
	char buff[20];
	
	printf("enter the string  :");
	fgets(buff,sizeof(buff),stdin);
	
	fd=open("/dev/sriuser", O_RDWR,0666 );

 	write( fd,buff,strlen(buff));

	read(fd,buff,sizeof(buff));
	printf("%s\n",buff);

	close(fd);
	return 0;
}
