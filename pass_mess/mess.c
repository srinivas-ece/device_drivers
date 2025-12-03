#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/init.h>

static char *var="hello";
module_param(var,charp,0644);

static int open(void){
	printk(KERN_INFO"%s\n",var);
	return 0;
}

static void close(void){
	printk(KERN_ALERT"bye\n");
}

MODULE_LICENSE("GPL");

module_init(open);
module_exit(close);
