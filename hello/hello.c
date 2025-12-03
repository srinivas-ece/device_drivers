#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
static int fun(void){
	printk(KERN_ALERT"hello srinivas\n");
	return 0;
	}

static void func(void){
	printk(KERN_INFO"byee srinivas!");
}

module_init(fun);
module_exit(func);

MODULE_LICENSE("GPL");
