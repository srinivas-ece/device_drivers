#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main(){
    int fd;

    fd=open("/dev/static_1",O_RDWR);
    
    if(fd < 0){
        printf("error");
        return -1;
    
    }
    char buffer[120]="strinai sljasdb";
    char rd_buff[120];
    write(fd,buffer,strlen(buffer));

    int red=read(fd,rd_buff,sizeof(rd_buff));

    rd_buff[red]='\0';

    printf("out :%s\n",rd_buff);



    close(fd);
    return 0;

}