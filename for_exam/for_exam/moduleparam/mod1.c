#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>

#include"head.h"

int my_add(int a,int b){
    return a+b;

}
EXPORT_SYMBOL(my_add);  

static int my_init(void){
    pr_info("add of 2 num");
    return 0;
}

static void my_exit(void){
       pr_info("bye...");
}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");
