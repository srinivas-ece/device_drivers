#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/jiffies.h>

struct timer_list my_tim;
int a=0;

 static void callback(struct timer_list * timer){
	pr_info("timeer on %d\n",a++);
	 mod_timer(&my_tim, jiffies + jiffies_to_msecs(5000));
 }


static int my_init(void){
	pr_info("starting code ");
	timer_setup(&my_tim, callback, 0);
	mod_timer(&my_tim, jiffies + jiffies_to_msecs(5000));
	return 0;
}

static void my_exit(void){
	pr_alert("end of code ");
	del_timer(&my_tim);
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
