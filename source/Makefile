obj-m += csc492.o
csc492-objs := main.o


all: clean
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

	# cleanup local folder
	rm -rf .tmp_versions
	rm .cache.mk 
	rm .csc492.ko.cmd
	rm .csc492.mod.o.cmd
	rm .csc492.o.cmd
	rm csc492.mod.c
	rm csc492.mod.o 
	rm main.o 
	rm Module.symvers 
	rm modules.order

	# move final module to build folder
	mv csc492.ko ../build

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -rf ../build/*

install:
	sudo insmod ../build/csc492.ko 

checkLog:
	sudo less +G /var/log/kern.log

uninstall:
	sudo rmmod csc492