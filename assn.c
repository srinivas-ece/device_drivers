#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/wait.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/timer.h>
#include<linux/mutex.h>
#include<linux/slab.h>


#define DEV_NAME "ass"
#define NUM_DEVICES 3
#define BUF_LEN 128

static dev_t dev_num;
static struct cdev cdev_arr[NUM_DEVICES];
static struct class *my_class;
static struct device *devs[NUM_DEVICES];

static struct timer_list my_timer;
static DEFINE_MUTEX(my_lock);
static DECLARE_WAIT_QUEUE_HEAD(my_wq);


static char msg1[BUF_LEN];
static char msg2[BUF_LEN];

static int data_ready=0;

static void my_timer_cb(struct timer_list *t){
	pr_info("timer expired : clearin message");

	mutex_lock(&my_lock);
	msg1[0] = '\0';
	msg2[0] = '\0';
	data_ready = 0;
	mutex_unlock(&my_lock);

	wake_up_interruptible(&my_wq);
}


static int my_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Opened minor %d\n", iminor(inode));
    return 0;
}

static int my_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Closed minor %d\n", iminor(inode));
    return 0;
}

static ssize_t my_write(struct file *file, const char __user *buf,
                        size_t len, loff_t *off){
	int minor = iminor(file->f_inode);
	char tmp[BUF_LEN];

	if(len >= BUF_LEN)
		len = BUF_LEN -1;
	if(copy_from_user(tmp,buf,len))
		return -EFAULT;
	tmp[len] = '\0';
	mutex_lock(&my_lock);

	if(minor == 0){
		strncpy(msg1,tmp,BUF_LEN);
		pr_info("dev0 worte : %s",msg1);
	}else if(minor == 1){
		strncpy(msg2,tmp,BUF_LEN);
		pr_info("dev1 worte : %s",msg2);
	}

	if(strlen(msg1)>0 && strlen(msg2)>0)
		data_ready = 1;

	mutex_unlock(&my_lock);

	wake_up_interruptible(&my_wq);

	mod_timer(&my_timer,jiffies + msecs_to_jiffies(10000));

	return len;
}

static ssize_t my_read(struct file *file, char __user *buf,
                       size_t len, loff_t *off){

    	char combined[BUF_LEN * 2];
    	int minor = iminor(file->f_inode);

    	if (minor != 2)
    	    return -EINVAL;

    	wait_event_interruptible(my_wq, data_ready == 1);

    	mutex_lock(&my_lock);
	snprintf(combined, sizeof(combined), "%s %s", msg1, msg2);
	if (len > strlen(combined))
        len = strlen(combined);

    	if (copy_to_user(buf, combined, len)) {
        mutex_unlock(&my_lock);
        return -EFAULT;
    }

    	mutex_unlock(&my_lock);

    	return len;
}


static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release,
    .read = my_read,
    .write = my_write,
};

static int my(void){
	int i;
	alloc_chrdev_region(&dev_num, 0, NUM_DEVICES, DEV_NAME);
	my_class=class_create(DEV_NAME);

	for( i = 0; i<NUM_DEVICES; i++){
		cdev_init(&cdev_arr[i],&fops);
		cdev_add(&cdev_arr[i],dev_num+i,1);
		devs[i]=device_create(my_class,NULL,dev_num+i,NULL,"ass%d",i);
	}

	pr_info("reistered 3 devices");
	timer_setup(&my_timer,my_timer_cb,0);
	return 0;
}


static void my_exit(void){
	int i;
	del_timer_sync(&my_timer);
	for(i=0 ;i<NUM_DEVICES; i++){
		device_destroy(my_class,dev_num+i);
		cdev_del(&cdev_arr[i]);
	}
	class_destroy(my_class);
	unregister_chrdev_region(dev_num, NUM_DEVICES);
	pr_info("module removed");
}

module_init(my);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SRI");



