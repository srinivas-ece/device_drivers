#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/spinlock.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>

#define DEV_NAME "sync"

static dev_t dev;
static struct cdev my_cdev;
static struct class *my_class;
static char k_buff[1034];
static char kr_buff[3333];
static spinlock_t my_lock;

static int my_open(struct inode *inode, struct file *file){
        printk(KERN_ALERT"sridyn : device open\n");
        return 0;
}

static int my_release(struct inode *inode, struct file *file){
        printk(KERN_ALERT"sridyn: device closed\n");
        return 0;
}

static ssize_t my_read(struct file *file, char __user *buf,
                       size_t len, loff_t *ppos)
{
    size_t to_copy = min(len, sizeof(k_buff));

    copy_to_user(buf, k_buff, to_copy);

    return to_copy;
}

static ssize_t my_write(struct file *file, const char __user *buf,
                        size_t len, loff_t *ppos)
{
    size_t to_copy = min(len, sizeof(k_buff) - 1);

    if (copy_from_user(k_buff, buf, to_copy))
        return -EFAULT;

    k_buff[to_copy] = '\0';  // IMPORTANT

    printk(KERN_INFO "write data = %s\n", k_buff);

    return to_copy;
}
static struct file_operations fops = {
        .owner   = THIS_MODULE,
        .open    = my_open,
        .release = my_release,
        .read    = my_read,
        .write   = my_write,
};


static int my(void){
    pr_info("salaar");
    alloc_chrdev_region(&dev,0,1,DEV_NAME);

    cdev_init(&my_cdev,&fops);
    cdev_add(&my_cdev,dev,1);

    my_class=class_create("my_class");
    device_create(my_class,NULL,dev,NULL,DEV_NAME);

    spin_lock_init(&my_lock);

    printk(KERN_INFO"major =%d  minor= %d\n",MAJOR(dev),MINOR(dev));

    return 0;
}

static void my_exit(void){
    pr_info("byee...");
    cdev_del(&my_cdev);
    device_destroy(my_class,dev);
    class_destroy(my_class);
    unregister_chrdev_region(dev,2);
    
}

module_init(my);
module_exit(my_exit);
MODULE_LICENSE("GPL");