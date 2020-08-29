/*
 *开门狗寄存器没有喂狗会cpu重启
 *需要关闭开门狗
 *通过看是否读写0号内存处判断nand还是nor启动（nor启动不能写0地址）
 */

 .text //代码段
 .global _start  声明全局标号_start

 _start:   //标号_start

    ldr r0, =0x53000000 //开门狗寄存器地址
	ldr r1, =0          //看门狗寄存器设为0，关闭
	str r1, [r0]        //写值

    mov r1, #0 //赋值r1 准备写到0地址
	ldr r0, [r1] /* 读出原来的值备份 */
	str r1, [r1] /* 0->[0] */ 
	ldr r2, [r1] /* r2=[0] */
	cmp r1, r2   /* r1==r2? 如果相等表示是NAND启动 */ 
    ldr sp, =0x40000000+4096 //nor的寻址地址在0x40000000开始，同样设置4k栈
    moveq sp, =4096   //nand 启动 栈由上往下生长,设置4k的栈   //moveq 如果判断等于执行
    streq r0, [r1]   /* 恢复原来的值 */  
 
    bl main
halt:
    b halt //死循环
