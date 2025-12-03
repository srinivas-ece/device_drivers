#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/atomic.h>

atomic_t counter;
static unsigned long flags = 0;
static int  __init mymod_init(void)
{
    atomic_set(&counter, 0);
    atomic_add(5,&counter);
    atomic_sub(4, &counter);
    atomic_inc(&counter);
    atomic_dec(&counter);
    pr_info("counter %d\n",atomic_read(&counter));

    set_bit(2, &flags);
    clear_bit(2, &flags);         
    change_bit(1, &flags);          
    change_bit(1, &flags);       
    printk(KERN_INFO "Bit 1 = %ld\n",flags);
    return  0;
}

static void __exit mymod_exit(void)
{
    printk(KERN_INFO "Module Removed\n");
}

module_init(mymod_init);
module_exit(mymod_exit);

MODULE_LICENSE("GPL");
