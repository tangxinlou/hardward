all:
	arm-linux-gcc -c -o led.o led.c
	arm-linux-gcc -c -o uart.o uart.c
	arm-linux-gcc -c -o init.o init.c
	arm-linux-gcc -c -o main.o main.c
	arm-linux-gcc -c -o start.o start.S
#   arm-linux-ld -Ttext 0  -Tdata 0x30000000 start.o led.o uart.o init.o main.o -o sdram.elf 把data 放到sdram中
#   但是使用这个30000000会让bin文件特别大
	arm-linux-ld -T sdram.lds start.o led.o uart.o init.o main.o -o sdram.elf
# 使用连接脚本实现
	arm-linux-objcopy -O binary -S sdram.elf sdram.bin
	arm-linux-objdump -D sdram.elf >sdram.dis
clean:
	rm *.bin *.o *.elf *.dis
