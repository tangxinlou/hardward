

void delay(volatile int d)
{
	while (d--);
}

int main()
{
    unsigned int *pGPFCON = (unsigned int *)0x56000050; //无符号int 型指针
	unsigned int *pGPFDAT = (unsigned int *)0x56000054; 
    if (which == 4)
    {
        /* 配置GPF4为输出引脚 */
        *pGPFCON = 0x100;
    }
    else if (which == 5)
    {
        /* 配置GPF5为输出引脚 */
        *pGPFCON = 0x400;
    }

    *pGPFDAT = 0;       //gpio 控制器gpf 数据寄存器

    return 0;
}
