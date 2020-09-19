#include "s3c2440_soc.h"
#include "uart.h"
#include "init.h"

char g_Char = 'A'; //初始化为非0的全局变量保存在数据段中
char g_Char3 = 'a';
const char g_Char2 = 'B'; //只读数据，保存在只读数据段中
int g_A = 0; //初始化为0的全局变量保存在bss段中
int g_B; //为初始化的全局变量保存在bss段中 
//局部变量保存在栈中

int main(void)
{
    led_init();
    //interrupt_init();
    key_eint_init();
    timer_init();

    puts("\n\rg_A = ");
    printHex(g_A);
    puts("\n\r");
    
   nor_flash_test(); 

    return 0;
}
