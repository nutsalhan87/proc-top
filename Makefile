obj-m += proc-top.o
proc-top-y := main.o top/top.o top/tasks/tasks.o top/summary/summary.o top/printer/printer.o

build:
	make -C $(KERNEL_PATH)/lib/modules/$(shell uname -r)/build M=$(shell pwd) modules
clean:
	make -C $(KERNEL_PATH)/lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
ins:
	sudo insmod proc-top.ko
rm:
	sudo rmmod proc_top
reins:
	make rm
	make build
	make ins