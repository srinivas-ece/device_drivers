#include<linux/module.h>
#include<linux/fs.h>
#include<linux/init.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>



#define DEVICE_NAME "srinivas"
#define MAJOR_NUM 2

static dev_t dev = MKDEV(MAJOR_NUM,0);
static struct cdev my_cdev;
static char kernel_buffer[120] ;

static int my_open(struct inode *inode,struct file *file){

	printk(KERN_ALERT"srinivas: device opend\n");
	return 0;
}

static int my_release(struct inode *inode ,struct file *file){
	  printk(KERN_ALERT"srinivas: device closed\n");
	  return 0;
}

static ssize_t my_read(struct file *file, char __user *buf, size_t count, loff_t *ppos){	
	printk(KERN_ALERT"srinivas: read request\n");
	if(copy_to_user(buf, kernel_buffer, count))
		return -EFAULT;
	return count;

}

static ssize_t my_write(struct file *file, const char __user *buf,size_t count, loff_t *f_pos){
	  printk(KERN_ALERT"srinivas: write request\n");

	  if (copy_from_user(kernel_buffer,buf, count))
		     return -EFAULT;
        return count;
}

static struct file_operations fops={
	.owner = THIS_MODULE,
	.open = my_open,
	.read = my_read,
	.write = my_write,
	.release = my_release,
};


static int __init my_init(void){
	 printk(KERN_ALERT"srinivas: init");
	//register_chrdev_region(dev,1,DEVICE_NAME);
	 if(register_chrdev_region(dev,1,DEVICE_NAME)<0){
		  printk(KERN_ALERT"could not register device number\n");
		  return -1;
	 }

	 cdev_init(&my_cdev,&fops);
	 if(cdev_add(&my_cdev,dev,1)<0){
		 unregister_chrdev_region(dev,1);
		  printk(KERN_ALERT"cdev_add failed\n");
		  return -1;
	 }

	 printk(KERN_INFO"srinivas: driver loaded successfully\n");
	 printk(KERN_INFO"create device using : mknod /dev/%s c %d 0\n",DEVICE_NAME, MAJOR_NUM);
	 return 0;
}

static void __exit my_exit(void){
	cdev_del(&my_cdev);
	unregister_chrdev_region(dev,1);
        printk(KERN_ALERT"srinivas: exit");
}


MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);

