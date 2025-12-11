#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/init.h>

static int my_init(void){
    pr_info("i am in start");
    return 0;
}

static void my_exit(void){
    pr_info("bye...");

}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");