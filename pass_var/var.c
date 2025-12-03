#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include <linux/stringify.h>
#include <linux/moduleparam.h>

static int var=20;
//MODULE_PARM_DESC(var, "An integer parameter");
module_param(var, int, 0644);


static int fun(void){
	printk(KERN_ALERT"%d\n",var);
        return 0;
        }


static void func(void){
        printk(KERN_INFO"byee srinivas!");
}

module_init(fun);
module_exit(func);

MODULE_LICENSE("GPL");

