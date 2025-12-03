#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(){

    int fd = open("/dev/sync",O_RDWR);
    

    char data1[] = "aaaaaa";
    char data2[] = "bbbbbb";

    for(int i = 0; i<100000; i++){
        write(fd,data1,strlen(data1));
        usleep(10);
    }
    close(fd);
}