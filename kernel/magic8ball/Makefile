KDIR=/lib/modules/`uname -r`/build
NAME=8ball

kbuild:
	make -C $(KDIR) M=`pwd`

install:
	sudo insmod $(NAME).ko
	sudo chmod 666 /dev/$(NAME)

clean:
	make -C $(KDIR) M=`pwd` clean

