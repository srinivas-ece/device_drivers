#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/init.h>

#define  DEVICE_NAME "sridyn"

static struct class *my_class; 
static dev_t dev;
static struct cdev my_cdev;
static char kernel_buffer[1024];

static int my_open(struct inode *inode, struct file *file){
        printk(KERN_ALERT"sridyn : device open\n");
        return 0;
}

static int my_release(struct inode *inode, struct file *file){
        printk(KERN_ALERT"sridyn: device closed\n");
        return 0;
}

static ssize_t my_read(struct file *file, char __user *buf, size_t len, loff_t *ppos){
        printk(KERN_ALERT"sridyn : read request\n");
        if(copy_to_user(buf,kernel_buffer,len))
                        return -EFAULT;

                return len;
}

static ssize_t my_write(struct file *file, const char __user *buf,size_t len, loff_t *ppos){
        printk(KERN_ALERT"sridyn: write request\n");
        if(copy_from_user(kernel_buffer,buf,len))
                return -EFAULT;

        return len;
}


static struct file_operations fops = {
        .owner   = THIS_MODULE,
        .open    = my_open,
        .release = my_release,
        .read    = my_read,
        .write   = my_write,
};

static int my_init(void){
        printk(KERN_ALERT"sridyn : init\n");
        if(alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME)<0){
                printk(KERN_ALERT"could not register device \n");
                 return -1;
        }
        cdev_init(&my_cdev,&fops);
        cdev_add(&my_cdev,dev,1);

	my_class=class_create("myclass");
	device_create(my_class,NULL,dev,NULL,DEVICE_NAME);
            
        printk(KERN_INFO"sridyn : dyn driver loaded successfully\n");
        printk(KERN_INFO"major =%d  minor= %d\n",MAJOR(dev),MINOR(dev));

        return 0;
}

static void my_exit(void){
        printk(KERN_ALERT"sri : exit\n");
        cdev_del(&my_cdev);
        device_destroy(my_class,dev);
        class_destroy(my_class);
        unregister_chrdev_region(dev,1);
}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");

