

void delay(volatile int d)
{
	while (d--);
}

int main()
{
    unsigned int *pGPFCON = (unsigned int *)0x56000050; //无符号int 型指针
	unsigned int *pGPFDAT = (unsigned int *)0x56000054; 
    int val = 0;  /* val: 0b000, 0b111 */
    /*
     * 000 取反 0b111 全不亮
     * 001 取反 110   亮4号灯
     * 010 取反 101   亮5号灯
     * 011 取反 100   亮45号灯
     * 100 取反 011   亮6号灯
     * 101 取反 010   亮64 号灯
     * 110 取反 001   亮56号灯
     * 111 取反 000   全亮
	int tmp;

	/* 设置GPFCON让GPF4/5/6配置为输出引脚 */
	*pGPFCON &= ~((3<<8) | (3<<10) | (3<<12)); //清除配置寄存器456 的设置
	*pGPFCON |=  ((1<<8) | (1<<10) | (1<<12)); //设置配置寄存器456 为输出 

	/* 循环点亮 */
	while (1)
	{
		tmp = ~val;
		tmp &= 7;//清除出456号gpio的设置
		*pGPFDAT &= ~(7<<4);456号数据寄存器清零
		*pGPFDAT |= (tmp<<4);电灯4|5|6
		delay(100000);//延时
		val++;
		if (val == 8)//循环计数
			val =0; 

    return 0;
}
