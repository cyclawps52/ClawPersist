obj-m += main.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

	# cleanup local folder
	rm -rf .tmp_versions
	rm .cache.mk 
	rm .main.ko.cmd
	rm .main.mod.o.cmd
	rm .main.o.cmd

	# move all pieces to build folder
	mv main.ko ../build/492.ko
	mv main.mod.c ../build
	mv main.mod.o ../build
	mv main.o ../build
	mv Module.symvers ../build
	mv modules.order ../build

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -rf ../build/*