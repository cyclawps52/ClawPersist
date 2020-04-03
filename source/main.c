#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tristan Fletcher (@Cyclawps52)");
MODULE_DESCRIPTION("CSC492 Final Project");
MODULE_VERSION("testing-01");


int init_module(void){
    printk(KERN_INFO "Hello world!\n");

    return 0; // any non zero value returned indicated module failed to load
}

void cleanup_module(void){
    printk(KERN_INFO "Goodbye world!\n");
}
