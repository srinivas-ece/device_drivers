obj-m += con.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
run:
	
	sudo insmod con.ko
	sudo chmod 666 /dev/sri_u
	sudo dmesg
test:
	sudo dmesg


