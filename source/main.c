#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tristan Fletcher (@Cyclawps52)");
MODULE_DESCRIPTION("CSC492 Final Project");
MODULE_VERSION("beta-rev5");


// parameter callbackIP
static char *callbackIP = "127.0.0.1"; 
module_param(callbackIP, charp, 0644);
MODULE_PARM_DESC(callbackIP, "Currently a placeholder for a future callback IP");

// parameter testInt
static int testInt = 0;
module_param(testInt, int, 0644)
MODULE_PARM_DESC(testInt, "a dummy integer used for testing file permissions");

// parameter testArray
static int testArray[2] = {0};
static int testArray_c = 0;
module_param_array(testArray, int, &testArray_c, 0000);
MODULE_PARM_DESC(testArray, "a dummy array used for testing file permissions");

int initModule(void){
    int i = 0;
    printk(KERN_INFO "[CSC492] Hello world!\n");
    printk(KERN_INFO "[CSC492] DEBUG: Callback IP set to %s\n", callbackIP);

    // testing file permission and modification
    printk(KERN_INFO "[CSC492] DUMMY: testInt has a value of %d\n", testInt);
    for(i=0; i<testArray_c; i++){
        printk(KERN_INFO "[CSC492] DUMMY: testArray[%d] has value %d\n", i, testArray[i]);
    }

    return 0;
}

void exitModule(void){
    printk(KERN_INFO "[CSC492] Goodbye world!\n");
}


module_init(initModule);
module_exit(exitModule);