# ClawPersist
_A red team assistive kernel module for linux-based systems created to satisfy the final project requirements of the CSC492 class at DSU_

## What is this?

This was an idea I had to fufill the requirements of the CSC492 Advanced Linux topics class at DSU. I hadn't really worked with writing kernel modules and was barely used to the idea of separate kernel and user space so I wanted to deep dive into something related to that topic. In short, during our mock CCDC competitions we normally have root access at minute zero with default credentials. The idea was to put in a backdoor that lies in kernelspace waiting for activation. This module creates a world-readable device and monitors read activity on said device. Any read of the device (can be done by a simple `cat` command) will trigger a backdoor `nc` bind shell on port 1337. So even if you get locked out of root, as long as you can code exec somewhere (whether that's from a low-level user or from a code injection vuln on a website), you can spawn that 1337 shell.

There are a few important notes about this module:

* I assume the box has `nc` on it and that `nc` will remain on it since most of the linux boxes in our environments have this by default.
* The initial PoC will not persist on a reboot. If I ever get around to writing the metasploit module to go with this, I would make sure the module is ran at reboot as well by utilizing the `/etc/modules` utility.
* The initial PoC is still very noisy. It outputs some debug stuff to the kernel log on load, runtime, and exit. Additionally the spawned shell is very noticable, the idea is that this bind shell would be used to spawn stealthier ways of access.

## How to use

Upon cloning the repo, there will be a makefile inside of the `source` directory. This file has a few options:

* `make` will simply build the final kernel module from source (assuming headers and build-essentials are installed)
* `make install` will load the kernel module
* `make checkLog` will open up `var/log/kern.log` to analyze the debug messages outputted by the module
* `make uninstall` will unload the kernel module and delete any of the items that spawn if the backdoor is triggered
* `make clean` removed all files from the build directory.

All of these actions can also be automated in quick succesion by utilizing the `controller.py` script.

## Future plans

There is still more I'd like to achieve with this project. More details can be found on the [tastlisk page](https://github.com/cyclawps52/ClawPersist/blob/master/taskList.md) along with some notes taken during the development of my initial PoC.

## Show me!

I have recorded a short `asciinema` demo of how the PoC (IE: `release-1`) works.
[![asciicast](https://asciinema.org/a/dBNhExoLyGAJ6Muq2W6a1f4xE.svg)](https://asciinema.org/a/dBNhExoLyGAJ6Muq2W6a1f4xE)