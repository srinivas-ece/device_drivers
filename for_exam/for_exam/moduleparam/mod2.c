#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>

#include"head.h"

static int a=10;
static int b=20;

static int my_init(void){
    pr_info("i am in start");
    pr_info("%d",my_add(a,b));
    return 0;
}

static void my_exit(void){
    pr_info("bye...");

}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");