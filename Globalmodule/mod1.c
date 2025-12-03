#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>

int my_add(int a,int b){
	return (a+b);
}
EXPORT_SYMBOL(my_add);

static int my_init(void){
	printk(KERN_ALERT"add of number\n");
	return 0;
}

static void my_exit(void){
	printk(KERN_INFO"bye...\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
