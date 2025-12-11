obj-m += mod1.o
obj-m += mod2.o

all :
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

clean :
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean

install :
	sudo mkdir -p /lib/modules/$(shell uname -r)/extra
	sudo cp mod1.ko /lib/modules/$(shell uname -r)/extra/
	sudo cp mod2.ko /lib/modules/$(shell uname -r)/extra/