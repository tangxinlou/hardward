#include "s3c2440_soc.h"

void uart0_init()
{
    GPHCON &= ~((3<<4) | (3<<6));
    GPHCON |= ((2<<4) | (2<<6));

    GPHUP &= ~((1<<2) | (1<<3));

    UCON0 = 0X00000005;
    UBRDIV0 = 26;

    ULCON0 = 0X00000003;
    
}

int putchar(int c)
{
    while(!(UTRSTAT0 & (1<<2)));
    UTXH0 = (unsigned char)c;

}

int getchar(void)
{
    while(!(UTRSTAT0 & (1<<0)));
    return URXH0;
}

int puts(const char *s)
{
    while(*s)
    {
        putchar(*s);
        s++;
    }
}

/*0xABCDEF12*/
void printHex(unsigned int val)
{
    int i;
    unsigned char arr[8];
    for(i = 0;i < 8; i++)
    {
        arr[0] = val & 0xf;
        val >>= 4;
    }

    for(i = 7;i >=0; i--)
    {
        if (arr[i] >= 0 && arr[i] <= 9)
            putchar(arr[i] + '0');
        else if(arr[i] >= 0xA && arr[i] <= 0xF)
            putchar(arr[i] - 0xA + 'A'); 
    }
}

void print1(void)
{
    puts("abc\n\r");
}

void print2(void)
{
    puts("123\n\r");
}

void printSWIVal(unsigned int *pSWI)
{
    puts("SWI val = ");
    printHex(*pSWI & ~0xff000000);
    puts("\n\r");
}








