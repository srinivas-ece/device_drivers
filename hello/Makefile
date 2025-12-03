
obj-m :=hello.o

kdir :=/lib/modules/$(shell uname -r)/build

PWD :=$(shell pwd)

all:
	make -C $(kdir) M=$(PWD) modules

clear:
	make -C $(kdir) M=$(PWD) clean
