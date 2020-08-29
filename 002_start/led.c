



int main()
{
    unsigned int *pGPFCON = (unsigned int *)0x56000050; //无符号int 型指针
	unsigned int *pGPFDAT = (unsigned int *)0x56000054; 

    *pGPFCON = 0x100;   //gpio 控制器gpf配置寄存器

    *pGPFDAT = 0;       //gpio 控制器gpf 数据寄存器

    return 0;
}
