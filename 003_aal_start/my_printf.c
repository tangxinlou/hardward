#include "my_printf.h"

//处理可变参数的宏

typedef char * va_list;

#define _INTSIZEOF(n) ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))  //4字节对齐

#define va_start(ap,v) ( ap = (va_list)&v + _INTSIZEOF(v) )

#define va_arg(ap,t)  (*(t *)(ap = ap + _INTSIZEOF(t), ap - _INTSIZEOF(t)))
#define va_end(ap)   ( ap = (va_list)0 )

unsigned char hex_tab[] = {'0','1','2','3','4','5','6','7',\
                           '8','9','a','b','c','d','e','f'};

static int outc(int c)         //打印字符
{
    __out_putchar(c);
    return 0;
}

static int outs (const char *s) //打印字符串
{
    while( *s != '\0')
        __out_putchar(*s++);
    return 0;
}

static int out_num(long n, int) //根据不同进制打印数字
{
 	unsigned long m=0;
	char buf[MAX_NUMBER_BYTES], *s = buf + sizeof(buf);
	int count=0,i=0;
			

	*--s = '\0';
	
	if (n < 0){
		m = -n;
	}
	else{
		m = n;
	}
	
	do{
		*--s = hex_tab[m%base];
		count++;
	}while ((m /= base) != 0);
	
	if( maxwidth && count < maxwidth){
		for (i=maxwidth - count; i; i--)	
			*--s = lead;
    }

	if (n < 0)
		*--s = '-';
	
	return outs(s); 
}


 static int my_vprintf(const char *fmt, va_list ap) 
{
	char lead=' ';
	int  maxwidth=0;
	
	 for(; *fmt != '\0'; fmt++) //把fmt 中不是%的字符都一个个打印
	 {
			if (*fmt != '%') {
				outc(*fmt);
				continue;
			}
			
		//format : %08d, %8d,%d,%u,%x,%f,%c,%s 
		    fmt++;       //fmt 中是%，略过+1
		if(*fmt == '0'){
			lead = '0';
			fmt++;	
		}

		lead=' ';
		maxwidth=0;
		
		while(*fmt >= '0' && *fmt <= '9'){ //可用位
			maxwidth *=10;
			maxwidth += (*fmt - '0');
			fmt++;
		}
		
			switch (*fmt) {                //根据类型调用不同字符组织函数
		case 'd': out_num(va_arg(ap, int),          10,lead,maxwidth); break; 
                  //根据类型调整指针ap的位置,使得ap指向下一个位置，里面是两步，取值，移动指针
		case 'o': out_num(va_arg(ap, unsigned int),  8,lead,maxwidth); break;				
		case 'u': out_num(va_arg(ap, unsigned int), 10,lead,maxwidth); break;
		case 'x': out_num(va_arg(ap, unsigned int), 16,lead,maxwidth); break;
			case 'c': outc(va_arg(ap, int   )); break;		
			case 's': outs(va_arg(ap, char *)); break;		  		
				
			default:  
				outc(*fmt);
				break;
			}
	}
	return 0;
}


 int printf(const char *fmt, ...) 
{
	va_list ap;  //char * ap 定义一个指针

	va_start(ap, fmt);    //fmt 是一个指针，这个指针大小是4字节，需要4字节空间保存。
                          //将指针ap 指向fmt保存地址后面，也就是&fmt + 4处
                          
	my_vprintf(fmt, ap);  //打印格式和可变参数  
	va_end(ap);           //char * ap 不用了，指向0
	return 0;
}

/*
 * 函数调用时，函数参数从左到右一个个入栈保存
 */
int my_printf_test(void)
{
	printf("This is www.100ask.org   my_printf test\n\r") ;	
	printf("test char           =%c,%c\n\r", 'A','a') ;	
	printf("test decimal number =%d\n\r",    123456) ;
	printf("test decimal number =%d\n\r",    -123456) ;	
	printf("test hex     number =0x%x\n\r",  0x55aa55aa) ;	
	printf("test string         =%s\n\r",    "www.100ask.org") ;	
	printf("num=%08d\n\r",   12345);
	printf("num=%8d\n\r",    12345);
	printf("num=0x%08x\n\r", 0x12345);
	printf("num=0x%8x\n\r",  0x12345);
	printf("num=0x%02x\n\r", 0x1);
	printf("num=0x%2x\n\r",  0x1);

	printf("num=%05d\n\r", 0x1);
	printf("num=%5d\n\r",  0x1);

	return 0;       
}
 





