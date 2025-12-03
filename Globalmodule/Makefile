obj-m +=mod1.o
obj-m +=mod2.o
obj-m +=mod3.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean

install:
	sudo mkdir -p /lib/modules/6.14.0-33-generic/extra
	sudo cp mod1.ko /lib/modules/6.14.0-33-generic/extra/
	sudo cp mod2.ko /lib/modules/6.14.0-33-generic/extra/
	sudo cp mod3.ko /lib/modules/6.14.0-33-generic/extra/

update:
	sudo depmod -a
