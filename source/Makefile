obj-m += clawpersist.o
clawpersist-objs := main.o


all: clean
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

	# cleanup local folder
	rm -rf .tmp_versions
	rm .cache.mk 
	rm .clawpersist.ko.cmd
	rm .clawpersist.mod.o.cmd
	rm .clawpersist.o.cmd
	rm clawpersist.mod.c
	rm clawpersist.mod.o 
	rm main.o 
	rm Module.symvers 
	rm modules.order

	# move final module to build folder
	mv clawpersist.ko ../build

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -rf ../build/*

install:
	sudo insmod ../build/clawpersist.ko 

checkLog:
	sudo less +G /var/log/kern.log

uninstall:
	sudo rmmod clawpersist