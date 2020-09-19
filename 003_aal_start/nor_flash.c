#include "my_printf.h"
#include "string_utils.h"

#define NOR_FLASH_BASE  0  /* jz2440, nor-->cs0, base addr = 0 */




void nor_write_word(unsigned int base, unsigned int offset, unsigned int val)
{
    volatile unsigned short *p = (volatile unsigned short *)(base + (offset << 1));
    *p = val;
}

void nor_cmd(unsigned int offset, unsigned int cmd)
{
    nor_write_ward(NOR_FLASH_BASE, offset,cmd);
}

unsigned int  nor_read_word(unsigned int base, unsigned int offset)
{
    volatile unsigned short *p = (volatile unsigned short *)(base + (offset << 1));
    return *p;
}

unsigned int nor_dat(unsigned int offset)
{
    return nor_read_word(NOR_FLASH_BASE,offset);
}

void do_scan_nor_flash(void)
{
    char str[4];
    unsigned int size;
    nor_cmd(0x55,0x98);
    str[0] = nor_dat(0x10);
    str[1] = nor_dat(0x11);
    str[2] = nor_dat(0x12);
    str[3] = '\0'
    printf("str = %s\n\r", str);

    size = nor_dat(0x27);
    printf("nor size = 0x%x, %dm\n\r", size, size/(1024*1024));

    nor_cmd(0,0xf0);

}
 void nor_flash_test(void)
{
	char c;

	while (1)
	{
		/* 打印菜单, 供我们选择测试内容 */
		printf("[s] Scan nor flash\n\r");
		printf("[e] Erase nor flash\n\r");
		printf("[w] Write nor flash\n\r");
		printf("[r] Read nor flash\n\r");
		printf("[q] quit\n\r");
		printf("Enter selection: ");

		c = getchar();
		printf("%c\n\r", c);

		/* 测试内容:
		 * 1. 识别nor flash
		 * 2. 擦除nor flash某个扇区
		 * 3. 编写某个地址
		 * 4. 读某个地址
		 */
		switch (c)		 
		{
			case 'q':
			case 'Q':
				return;
				break;
				
			case 's':
			case 'S':
				do_scan_nor_flash();
				break;

			case 'e':
			case 'E':
				do_erase_nor_flash();
				break;

			case 'w':
			case 'W':
				do_write_nor_flash();
				break;

			case 'r':
			case 'R':
				do_read_nor_flash();
				break;
			default:
				break;
		}
	}
}
