#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/init.h>

MODULE_LICENSE("GPL");

static int var=4;
module_param(var,int,0644);  // from taking input from commend line

static char *name="srinivas";
module_param(name,charp,0644);

static int myarr[3]={1,3,4};
module_param_array(myarr,int ,NULL, 0644);


static int __init open(void){
    
	pr_alert("Array elements: %d\t%d\t%d", myarr[0], myarr[1], myarr[2]);
	printk(KERN_ALERT"%d\n",var);
	printk(KERN_ALERT"%s\n",name);
        return 0;
	}

static void  __exit close(void){
        pr_info("bye\n");
	}

module_init(open);
module_exit(close);
