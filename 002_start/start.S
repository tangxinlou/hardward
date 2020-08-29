/*
 *新的篇章，需要汇编调用c，需要设置栈
 */

 .text //代码段
 .global _start  声明全局标号_start

 _start:   //标号_start

    ldr sp, =4096   //nand 启动 栈由上往下生长,设置4k的栈
 // ldr sp, =0x40000000+4096 //nor的寻址地址在0x40000000开始，同样设置4k栈
    
    bl main //有返回值的跳转 

halt:
    b halt //死循环
