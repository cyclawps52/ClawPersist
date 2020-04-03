# CSC492-Final
A red team assistive kernel module for linux-based systems created to satisfy the final project requirements of the CSC492 class at DSU

## Completed Tasks

* Writing a simple kernel module (akin to Hello World)
    * version `testing-01` to version `alpha-rev0`
    * What I learned: Makefiles are picky with kernel module naming and I hate it. Also, you can start the `less` command at the end of a file with the `+G` flag.

## Remaining Tasks

* Parameterizing the module
* Creating the world-writable device
* Interacting with the device via user land
* Allowing the kernel module to respond to user land interactions
* Running something in user land as root from kernel space
* Opening a bind shell as root from kernel space
* [Stretch] Wrapping all of this into a self-contained Metasploit module
* [Stretch] Creating a persistent Cobalt Strike C2 beacon from kernel space
