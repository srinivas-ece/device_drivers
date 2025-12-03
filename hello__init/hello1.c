#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>

static int __init fun(void){
	pr_info("hello sri");
	return 0;
}

static void __exit funn(void){
	pr_alert("bye bye..");
}

module_init(fun);
module_exit(funn);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SRINIVAS");

