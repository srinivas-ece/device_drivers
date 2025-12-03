#include<fcntl.h>
#include<stdio.h>
#include <unistd.h>

int main ()
{
	int fd;
	char buff[20];
	fd=open("/dev/sridyn", O_RDWR,0600 );
 	write( fd,"hello",5);
	read(fd,buff,sizeof(buff));
	printf("%s\n",buff);
	close(fd);
	return 0;
}
