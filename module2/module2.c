#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>


static int a=9;
static int b=34;
extern my_add(int ,int);

static int my_init(void){
        printk(KERN_ALERT"add of number: %d\n",my_add(a,b));
        return 0;
}

static void my_exit(void){
        printk(KERN_INFO"bye...\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
~                        
