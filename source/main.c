#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tristan Fletcher (@Cyclawps52)");
MODULE_DESCRIPTION("CSC492 Final Project");
MODULE_VERSION("beta-rev0");


// parameter callbackIP
static char *callbackIP = "127.0.0.1"; 
module_param(callbackIP, charp, S_IRUGO);
MODULE_PARAM_DESC(callbackIP, "Currently a placeholder for a future callback IP");

int initModule(void){
    printk(KERN_INFO, "[CSC492] Hello world!\n");
    printk(KERN_INFO, "[CSC492] DEBUG: Callback IP set to %s\n", callbackIP);

    return 0;
}

void exitModule(void){
    printk(KERN_INFO "[CSC492] Goodbye world!\n");
}


module_init(initModule);
module_exit(exitModule);