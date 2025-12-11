#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/uaccess.h>
#include<linux/cdev.h>
#include<linux/ioctl.h>

#define serial_magic 'a'

#define cmd_write  _IOW(serial_magic,1,char *)
#define cmd_age    _IOR(serial_magic,2,int *)

#define DEV_NAME "ioctl"
#define size 1048


static struct cdev cdev;
static struct class *my_class;
static dev_t dev;
static char k_buff[size];
static int k_age =10;

static int open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "sri_ioctl: Device opened\n");
    return 0;
}

static int close(struct inode *inode, struct file *file) {
    printk(KERN_INFO "sri_ioctl: Device released\n");
    return 0;
}


static ssize_t rd(struct file *file, char __user *buf,
			 size_t len, loff_t *ppos){
				if (copy_to_user(buf, k_buff, len))
					return -EFAULT;
				printk(KERN_ALERT"ioctl rd: %s",k_buff);
				return len;
			 }
static ssize_t wr(struct file *file, const char __user *buf,
			  size_t len, loff_t *ppos){
				if (copy_from_user(k_buff, buf, len))
						return -EFAULT;
				printk(KERN_ALERT"ioctl wr: %s",k_buff);
				return len;
			  }


static long cmd_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
	switch(cmd){
		case cmd_write :
				if (copy_from_user(k_buff,(char *)arg, size))
						return -EFAULT;
				printk(KERN_ALERT"ioctl cmd write : %s",k_buff);		
				break;
		
		case cmd_age :
				if (copy_to_user((int *)arg,&k_age, sizeof(k_age)))
						return -EFAULT;
				pr_info("ioctl cmd_age : %d",k_age);		

				break;

		default :
				break;		


	}
return 0;
}
static struct file_operations fops = {			
	.owner	 = THIS_MODULE,					
	.open	 = open,				
	.release = close,				
	.read	 = rd,					
	.write	 = wr,
	.unlocked_ioctl =cmd_ioctl,					
};

static int myi(void){
	pr_info("start");
	alloc_chrdev_region(&dev,0,1,DEV_NAME);

	cdev_init(&cdev,&fops);
	cdev_add(&cdev,dev,1);

	my_class = class_create( DEV_NAME);

	device_create(my_class,NULL,dev,NULL,DEV_NAME);

	pr_info("%d and %d",MAJOR(dev),MINOR(dev));

	return 0;
}

static void mye(void){
	device_destroy(my_class,dev);
	class_destroy(my_class);

	cdev_del(&cdev);
	unregister_chrdev_region(dev,1);
}
 module_init(myi);
 module_exit(mye);
 MODULE_LICENSE("GPL");

