#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/uaccess.h>
#include<linux/cdev.h>

#include"sriiotl.h"

#define DEVICE_NAME "sri_iotl"

static dev_t dev_number;
static struct cdev my_cdev;
static struct class *my_class;

static char message[BUF_LEN]={0};

static int dev_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "sri_ioctl: Device opened\n");
    return 0;
}

static int dev_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "sri_ioctl: Device released\n");
    return 0;
}

static ssize_t dev_read(struct file *file, char __user *buf, size_t len, loff_t *ppos){
	if(len > BUF_LEN) len=BUF_LEN;
	if(copy_to_user(buf,message,len))
		return -EFAULT;
	pr_info("sri_ioctl: read %zu bytes\n",len);
	return len;
}


static ssize_t dev_write(struct file *file, const char __user *buf, size_t len, loff_t *ppos){
	if(len > BUF_LEN) len = BUF_LEN;
	if(copy_from_user(message , buf, len))
		return -EFAULT;
	pr_info("sri_ioctl: written  %zu bytes\n",len);
        return len;
}

static long dev_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
	switch(cmd){
		case CMD_SET_MGS:
			if(copy_from_user(&message, (char *) arg,BUF_LEN))
				return -EFAULT;
			printk("IOCTL: mgs set = %s\n",message);
			break;

		case CMD_TO_MGS:
			if(copy_to_user((char *)arg, &message,BUF_LEN))
				return -EFAULT;
			printk("IOCTL: mgs returned = %s\n", message);
			break;

		default :
			return -EINVAL;
	}
	return 0;
}
static struct file_operations fops={
	.owner = THIS_MODULE,
    	.open = dev_open,
    	.release = dev_release,
    	.read = dev_read,
   	.write = dev_write,
    	.unlocked_ioctl = dev_ioctl,
};


static int my_init(void){
	alloc_chrdev_region(&dev_number,0,1,DEVICE_NAME);
	pr_info("init ");
	printk(KERN_INFO "sri_ioctl: Allocated major %d minor %d\n", MAJOR(dev_number), MINOR(dev_number));
	cdev_init(&my_cdev,&fops);
	cdev_add(&my_cdev,dev_number,1);
	my_class = class_create(DEVICE_NAME);
	device_create(my_class, NULL, dev_number, NULL, DEVICE_NAME);
	printk(KERN_INFO "mychardev module loaded successfully\n");

	return 0;
}

static void my_exit(void){

	device_destroy(my_class,dev_number);
	class_destroy(my_class);
	cdev_del(&my_cdev);
	unregister_chrdev_region(dev_number, 1);

	pr_info("bye....");
}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");
