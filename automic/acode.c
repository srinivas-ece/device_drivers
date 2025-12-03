#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/atomic.h>

atomic_t counter;
static unsigned long flags = 0;
static int __init mymod_init(void)
{
    atomic_set(&counter, 0);        // counter = 0
    atomic_inc(&counter);           // counter++
    atomic_add(5, &counter);        // counter = counter + 5
    atomic_dec(&counter);           // counter--
    atomic_sub(2, &counter);        // counter = counter - 2
    atomic_add(20,&counter);
    printk(KERN_INFO "Counter = %d\n", atomic_read(&counter));
   // printk(KERN_INFO "Counter = %d\n", counter);




    printk(KERN_INFO "Bit flag= %ld\n",flags);

    //-------------------------------------------------------------------------------

    
    set_bit(2, &flags);              // 00000100
    clear_bit(2, &flags);            // 00000000
    change_bit(1, &flags);           // 00000010
    change_bit(1, &flags);           // toggles back to 0

    //printk(KERN_INFO "Bit 1 = %d\n", test_bit(1, &flags));

    if (test_and_set_bit(0, &flags))
        printk("Bit 0 was already set\n");
    else{
        printk("Bit 0 was 0, now set to 1\n");
        printk(KERN_INFO "Bit 1 = %ld\n",flags);
    }
    return 0;
}

static void __exit mymod_exit(void)
{
    printk(KERN_INFO "Module Removed\n");
}

module_init(mymod_init);
module_exit(mymod_exit);

MODULE_LICENSE("GPL");

