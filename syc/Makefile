obj-m += drive.o

KDIR := /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

run :
	./a
	./b

runn :
	gcc user1.c -o a
	gcc user2.c -o b