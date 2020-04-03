# CSC492-Final
A red team assistive kernel module for linux-based systems created to satisfy the final project requirements of the CSC492 class at DSU

## Completed Tasks

* Writing a simple kernel module (akin to Hello World)
    * version `testing-01` to version `alpha-rev0`
    * What I learned: Makefiles are picky with kernel module naming and I hate it. Also, you can start the `less` command at the end of a file with the `+G` flag.
* Parameterizing the module
    * version `beta-rev1` to version `beta-rev8`
    * What I learned: These are picky, especially permission bits. From my understanding, the permission bits can have three values:
        * S_IRUGO: world readable but cannot be changed
        * S_IRUGO|S_IWUSR: allows root to change parameter
        * 0000: only set at module load time, cannot change
    * I was not able to find anything allowing any user to edit the parameter (IE: 0777) which I thought might not be possible. This is why I decided I might need to create a world-writable device.
        * Root can modify while module is loaded in `/sys/module/csc492/parameters`. `chmod` flags look like a normal file, unsure why bits won't expand properly.
    * Kernel modules don't follow that one C rule that allows you to initialize a loop variable in the loop declaration (like `for(int i=0, i<blah, i++))`). Loop counters must be declared beforehand.
    * First time I ran into the issue of attempting to import a user-space library into kernel-space. Took a while to figure out why that wouldn't work.
    * I have forgotten a lot more C and Python than I remember... was pretty eye opening.
    * I am really bad at updating module version numbers.
    * If you have an array parameter, you can't overflow the array by passing more than your specified size in the code. DMA seems possible, but out of scope for the current project.

## Remaining Tasks

* Creating the world-writable device
* Interacting with the device via user land
* Allowing the kernel module to respond to user land interactions
* Running something in user land as root from kernel space
* Opening a bind shell as root from kernel space
* [Stretch] Wrapping all of this into a self-contained Metasploit module
* [Stretch] Creating a persistent Cobalt Strike C2 beacon from kernel space
