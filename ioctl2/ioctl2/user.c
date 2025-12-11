#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/ioctl.h>

#define serial_magic 'a'

#define cmd_write  _IOW(serial_magic,1,char *)
#define cmd_age    _IOR(serial_magic,2,int *)

int main(){
    int fd;
    fd= open("/dev/ioctl",O_RDWR);
    if(fd<0){
        perror("open");
    }

    char buff[120]="srinivas from user space";
    char buff1[120];

    write(fd,buff,strlen(buff));

    read(fd,buff1,sizeof(buff1));
    printf("%s\n",buff1);

    char ctl_buf[120]="ioctl mgs";
    int ctl_buf1;

    ioctl(fd,cmd_write,ctl_buf);

    ioctl(fd,cmd_age,&ctl_buf1);
    printf("age %d",ctl_buf1);
    return 0;
}