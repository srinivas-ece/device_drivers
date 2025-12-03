#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/init.h>

#define  DEVICE_NAME "sri"
#define  MAJOR_NUM 2

static dev_t dev=MKDEV(MAJOR_NUM,0);
static struct cdev my_cdev;
static char kernel_buffer[120];

static int my_open(struct inode *inode, struct file *file){
	printk(KERN_ALERT"sri : device open\n");
	return 0;
}

static int my_release(struct inode *inode, struct file *file){
	printk(KERN_ALERT"sri: device closed\n");
	return 0;
}

static ssize_t my_read(struct file *file, char __user *buf, size_t len, loff_t *ppos){
	printk(KERN_ALERT"sri: read request\n");
	if(copy_to_user(buf,kernel_buffer,len))
			return -EFAULT;
			
		return len;
}

static ssize_t my_write(struct file *file, const char __user *buf,size_t len, loff_t *ppos){
	printk(KERN_ALERT"srinivas: write request\n");
	if(copy_from_user(kernel_buffer,buf,len))
		return -EFAULT;

	return len;
}


static struct file_operations fops = {			
	.owner	 = THIS_MODULE,			
	.open	 = my_open,					
	.release = my_release,					
	.read	 = my_read,					
	.write	 = my_write,
};

static int my_init(void){
	printk(KERN_ALERT"sri : init\n");
	if(register_chrdev_region(dev,1,DEVICE_NAME)<0){
		printk(KERN_ALERT"could not register device \n");
      		 return -1;
	}
	cdev_init(&my_cdev,&fops);
	if(cdev_add(&my_cdev,dev,1)<0){
		unregister_chrdev_region(dev,1);
		printk(KERN_INFO"cdev_add failed\n");
		return -1;
	}
	printk(KERN_INFO"sri: driver loaded successfully\n");
	printk(KERN_INFO"create a driver using : mknod /dev/%s c %d 0\n",DEVICE_NAME,MAJOR_NUM);

        return 0;
}

static void my_exit(void){
	printk(KERN_ALERT"sri : exit\n");
	cdev_del(&my_cdev);
	unregister_chrdev_region(dev,1);
}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");

