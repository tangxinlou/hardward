#include "s3c2440_soc.h"


void interrupt_init()
{
    //使能 eint 0 eint 2 eint8_23
    INTMSK &= ~((1<<0) | (1<<2) | (1<<5));
}


void key_eint_init(void)
{
    GPFCON &= ~((3<<0) | (3<<4));
	GPFCON |= ((2<<0) | (2<<4));   /* S2,S3被配置为中断引脚 */

	GPGCON &= ~((3<<6) | (3<<22));
	GPGCON |= ((2<<6) | (2<<22));   /* S4,S5被配置为中断引脚 */ 


    EXTINT0 |= (7<<0) | (7<<8);     /* S2,S3 */
	EXTINT1 |= (7<<12);             /* S4 */
	EXTINT2 |= (7<<12);             /* S5 */ 

	EINTMASK &= ~((1<<11) | (1<<19));

}

void key_eint_irq(int irq)
{
    unsigned int val = EINTPEND;
	unsigned int val1 = GPFDAT;
	unsigned int val2 = GPGDAT;

    if(irq == 0)
    {
        if(val1 & (1<<0))
        {
            GPFDAT |= (1<<6);
        }
        else
        {
            GPFDAT |= ~(1<<6);
        }
        
        if(val1 & (1<<0))
        {
            GPFDAT |= (1<<6);
        }
        else
        {
            GPFDAT |= ~(1<<6);
        }

    }

    if(irq == 2)
    {
        if(val1 & (1<<2))
        {
            GPFDAT |= (1<<5);
        }
        else
        {
            GPFDAT |= ~(1<<5);
        }
    }

    if (irq == 5) /* eint8_23, eint11--s4 控制 D10, eint19---s5 控制所有LED */
    {
        if (val & (1<<11)) /* eint11 */
        {
            if (val2 & (1<<3)) /* s4 --> gpf4 */
            {
                /* 松开 */
                GPFDAT |= (1<<4);
            }
            else
            {
                /* 按下 */
                GPFDAT &= ~(1<<4);
            }
        }
        else if (val & (1<<19)) /* eint19 */
        {
            if (val2 & (1<<11))
            {
                /* 松开 */
                /* 熄灭所有LED */
                GPFDAT |= ((1<<4) | (1<<5) | (1<<6));
            }
            else
            {
                /* 按下: 点亮所有LED */
                GPFDAT &= ~((1<<4) | (1<<5) | (1<<6));
            }
        }
    }     


}
void handle_irq_c(void)
{
    int bit = INTOFFSET;

    if(bit == 0 || bit == 2 || bit == 5)
    {
        key_eint_irq(bit);
    }

    SRCPND = (1<<bit); //通过往相应位写1清零
	INTPND = (1<<bit);	 
}









