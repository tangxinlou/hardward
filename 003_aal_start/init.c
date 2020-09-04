#include "s3c2440_soc.h"

void bank0_tacc_set(int val)
{
    BANKCON0 = val << 8;
}

void sdram_init(void)
{
    BWSCON = 0x22000000;

	BANKCON6 = 0x18001;
	BANKCON7 = 0x18001;

	REFRESH  = 0x8404f5;

	BANKSIZE = 0xb1;

	MRSRB6   = 0x20;
	MRSRB7   = 0x20; 
}


int sdram_test(void)
{
    volatile unsigned char *p = (volatile unsigned char *)0x30000000;
    int i;

    for (i = 0; i < 1000;i++)
    {
        p[i] = 0x55;
    }

    for(i = 0; i < 1000; i++)
    {
        if(p[i] != 0x55)
            return -1;
    }
    return 0;
}

void copy2sdram(void)
{
    extern int __code_start, __bss_start;
    volatile unsigned int *dest = (volatile unsigned int *) &__code_start;
    volatile unsigned int *end = (volatile unsigned int *) &__bss_start;
    volatile unsigned int *src = 0;

    while(src)
    {
        *dest++ = *src;
    }
}

void clean_bss()
{            
    extern int _end, __bss_start;
    volatile unsigned int *start = (volatile unsigned int *)&__bss_start;
    volatile unsigned int *end = (volatile unsigned int *)&_end; 
    while(start < end)
    {
        *start++ = 0;
    }
}




















