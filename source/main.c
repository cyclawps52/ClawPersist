#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tristan Fletcher (@Cyclawps52)");
MODULE_DESCRIPTION("CSC492 Final Project");
MODULE_VERSION("charlie-rev2");

// PROTOTYPES - MOVE TO .H FILE LATER
int initModule(void);
void exitModule(void);
static int deviceOpen(struct inode*, struct file*);
static int deviceRelease(struct inode*, struct file*);
static ssize_t deviceRead(struct file*, char*, size_t, loff_t*);
static ssize_t deviceWrite(struct file*, const char*, size_t, loff_t*);

// for character device
#define SUCCESS 0
#define DEVICE_NAME "csc492dev"
#define BUF_LEN 256
static int major;
static int deviceOpenStatus = 0;
static char msg[BUF_LEN];
static char *msgPtr;
static struct file_operations fops = {
    .read = deviceRead,
    .write = deviceWrite,
    .open = deviceOpen,
    .release = deviceRelease
} ;

// parameter callbackIP
static char *callbackIP = "127.0.0.1"; 
module_param(callbackIP, charp, S_IRUGO);
MODULE_PARM_DESC(callbackIP, "Currently a placeholder for a future callback IP");

// parameter testInt
static int testInt = 52;
module_param(testInt, int, S_IRUGO|S_IWUSR);
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
    for(i=0; i<(sizeof(testArray) / sizeof(int)); i++){
        printk(KERN_INFO "[CSC492] DUMMY: testArray[%d] has value %d\n", i, testArray[i]);
    }

    // character device
    major = register_chrdev(0, DEVICE_NAME, &fops);
    if(major < 0){
        printk(KERN_ALERT "[CSC492] ERROR: Registering character device failed with %d\n", major);
        exitModule();
        return major;
    }
    printk(KERN_INFO "[CSC492] DEBUG: Assigned major number %d\n", major);

    return 0;
}

void exitModule(void){
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "[CSC492] Goodbye world!\n");
}

// cat /dev/csc492dev
static int deviceOpen(struct inode* inode, struct file* file)
{
	static int counter = 0;

	if (deviceOpenStatus)
		return -EBUSY;

	deviceOpenStatus++;
	sprintf(msg, "Counter is now at %d\n", counter++);
	msgPtr = msg;
	try_module_get(THIS_MODULE);

	return SUCCESS;
}

static int deviceRelease(struct inode* inode, struct file* file)
{
	deviceOpenStatus--;		
	module_put(THIS_MODULE);
	return 0;
}

static ssize_t deviceRead(struct file* filp, char* buffer, size_t length, loff_t* offset)
{
	int bytesRead = 0;

	if (*msgPtr == 0)
		return 0;

	while (length && *msgPtr) {
		put_user(*(msgPtr++), buffer++);
		length--;
		bytesRead++;
	}

	return bytesRead;
}

static ssize_t deviceWrite(struct file* filp, const char* buff, size_t len, loff_t* off)
{
	printk(KERN_INFO "[CSC492] INFO: Write to /dev/csc492dev detected but not supported\n");
	return -EINVAL;
}

module_init(initModule);
module_exit(exitModule);