#include<stdio.h>
#include <fcntl.h>
#include<signal.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include<stdlib.h>

#define MAGIC_num 'q'

#define LED_ON _IO(MAGIC_num,0)
#define LED_OFF _IO(MAGIC_num,1)
#define LED_SET _IOW(MAGIC_num,3,int)
#define LED_GET _IOR(MAGIC_num,4,int)
int fd;

void handle(int sig){
	close(fd);
	printf("close success");
	exit(0);
}



int main(){
    signal(SIGINT,handle);

    fd = open("/dev/led_glow", O_RDWR);
    if(fd < 0){
        perror("open");
        return 0;
    }

    while(1){
        ioctl(fd, LED_ON);
        sleep(1);
        ioctl(fd, LED_OFF);
        sleep(1);
    }
}
