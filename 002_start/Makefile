all:
	arm-linux-gcc -c -o led.o led.c
	arm-linux-gcc -c -o start.o start.S
#设置代码段链接地址是0 start.o he led.o 依次放置,输出可执行文件
	arm-linux-ld -Ttext 0 start.o led.o -o led.elf
#将生成的可执行文件转化为二进制文件
	arm-linux-objcopy -O binnary -S led.elf led.bin
	arm-linux-objdump -D led.elf >led.dis
