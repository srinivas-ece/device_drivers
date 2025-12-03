#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/uaccess.h>
#include<linux/cdev.h>


#define DEVICE_NAME "sri_u"
#define BUF_LEN 2024

static dev_t dev_number;
static struct cdev my_cdev;
static struct class *my_class;

static char message[BUF_LEN] = "";
static int msg_len = 0;

static ssize_t dev_write(struct file *file, const char __user *buf, size_t len, loff_t *ppos){
  //  int space_left = BUF_LEN - msg_len - 2;

    // if(*ppos + len > BUF_LEN)
    //     len = BUF_LEN;

    if(len < 0)
        return -ENOSPC;

    if(copy_from_user(message + *ppos, buf, len)<0)
        return -EFAULT;

    *ppos += len;
     message[len] = '\0';

    pr_info("APPEND OK: %s\n", message);
    return len;
}

static ssize_t dev_read(struct file *file, char __user *buf, size_t len, loff_t *ppos){

    if(copy_to_user(buf, message, len))
        return -EFAULT;

    return len;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .write = dev_write,
    .read = dev_read,
};

static int my_init(void){
    alloc_chrdev_region(&dev_number,0,1,DEVICE_NAME);

    cdev_init(&my_cdev,&fops);
    cdev_add(&my_cdev,dev_number,1);

    my_class = class_create(DEVICE_NAME);
    device_create(my_class, NULL, dev_number, NULL, DEVICE_NAME);

    printk("Kernel module loaded\n");
    return 0;
}

static void my_exit(void){
    device_destroy(my_class, dev_number);
    class_destroy(my_class);

    cdev_del(&my_cdev);
    unregister_chrdev_region(dev_number,1);
}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");

