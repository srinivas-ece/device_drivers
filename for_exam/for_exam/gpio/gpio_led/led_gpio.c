#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/uaccess.h>
#include<linux/gpio/consumer.h>
#include<linux/ioctl.h>
#include<linux/platform_device.h>
#include<linux/cdev.h>
#include<linux/of.h>
#include<linux/of_device.h>

#define DEVICE_NAME "led_glow"

// ioctl//

#define MAGIC_num 'q'

#define LED_ON _IO(MAGIC_num,0)
#define LED_OFF _IO(MAGIC_num,1)
#define LED_SET _IOW(MAGIC_num,3,int)
#define LED_GET _IOR(MAGIC_num,4,int)

//globals//

static dev_t led_dev;
static struct cdev led_cdev;
static struct class *my_class;
static struct gpio_desc *led_gpio;

//ioctl modules//


static long led_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
    int value;

    switch(cmd){
        case LED_ON :
             gpiod_set_value_cansleep(led_gpio, 1);
            break;

        case LED_OFF :
            gpiod_set_value_cansleep(led_gpio, 0);
            break;

        case LED_SET :
            if(copy_from_user(&value,(int *)arg,sizeof(value)))
                return -EFAULT;
            gpiod_set_value_cansleep(led_gpio,value ? 1 : 0);
            break;

        case LED_GET :
          	value =  gpiod_get_value_cansleep(led_gpio);
            if(copy_to_user((int *)arg,&value,sizeof(value)))
                return -EFAULT;
            break;
        
        default :
            break;

    }
    return 0;
}

static const struct file_operations led_fops = {			
	.owner	 = THIS_MODULE,	
    .unlocked_ioctl = led_ioctl ,
};

static int my_probe(struct platform_device *pdev){
    pr_info("i am in my_start");

    led_gpio = gpiod_get(&pdev->dev,"led",GPIOD_OUT_LOW);

    alloc_chrdev_region(&led_dev,0,1,DEVICE_NAME);
    cdev_init(&led_cdev,&led_fops);
    cdev_add(&led_cdev,led_dev,1);
    my_class = class_create(DEVICE_NAME);
    device_create(my_class,NULL,led_dev,NULL,DEVICE_NAME);

    return 0;
}

static void my_remove(struct platform_device *pdev){
    gpiod_put(led_gpio);
    device_destroy(my_class,led_dev);
    class_destroy(my_class);
    cdev_del(&led_cdev);
    unregister_chrdev_region(led_dev,1);
}

static const struct of_device_id led_match_table[] = {
	{ .compatible = "mycompany,rpi-gpio-led" },
    	{ }
};

MODULE_DEVICE_TABLE(of,led_match_table);

struct platform_driver led_platform = {
    .probe = my_probe,
    .remove = my_remove,
    .driver =   {
         .name           = "rpi-gpio-led-driver-ioctl",
        .of_match_table = led_match_table,
    },
}; 

module_platform_driver(led_platform);

MODULE_LICENSE("GPL");