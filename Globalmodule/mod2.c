#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include"head.h"

//main

static int a=10;
static int b=20;

//extern  int my_add(int a,int b);

static int my_init(void){
        printk(KERN_ALERT"add of number: %d\n",my_add(a,b));
      	printk(KERN_ALERT"sub of number: %d\n",sub(a,b));
      	return 0;
}

static void my_exit(void){
        printk(KERN_INFO"bye...\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");                        
