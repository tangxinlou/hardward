
.text
.global _start
_start:
    b reset
    //ldr pc, =do_und //仅仅跳转指令是绝对地址，由于do_und 会保存在当前汇编文件最后，则do_und 可能会
    //保存在超过4k地方
    ldr pc, =und_addr
und_addr:
    .work do_und

do_und:
    ldr sp, = 0x34000000
    stmdb sp!, {r0~r12, lr}

    mrs r0, cpsr
    ldr r1, =und_string
    bl printException //bl 是相对跳转，如果是nand跳转,printException被重定位到了sdram 超过4k，则会出错
    //所以应该使用绝对地址

    ldmia sp!, {r0~r12, lr}^

und_string:
    .string "undefined instruction exception"

.align 4 //4字节对齐
reset:

    /* 关闭看门狗 */
	ldr r0, =0x53000000
	ldr r1, =0
	str r1, [r0]

	/* 设置MPLL, FCLK : HCLK : PCLK = 400m : 100m : 50m */
	/* LOCKTIME(0x4C000000) = 0xFFFFFFFF */
	ldr r0, =0x4C000000
	ldr r1, =0xFFFFFFFF
	str r1, [r0]

	/* CLKDIVN(0x4C000014) = 0X5, tFCLK:tHCLK:tPCLK = 1:4:8  */
	ldr r0, =0x4C000014
	ldr r1, =0x5
	str r1, [r0]

	/* 设置CPU工作于异步模式 */
	mrc p15,0,r0,c1,c0,0
	orr r0,r0,#0xc0000000   //R1_nF:OR:R1_iA
	mcr p15,0,r0,c1,c0,0

	/* 设置MPLLCON(0x4C000004) = (92<<12)|(1<<4)|(1<<0) 
	 *  m = MDIV+8 = 92+8=100
	 *  p = PDIV+2 = 1+2 = 3
	 *  s = SDIV = 1
	 *  FCLK = 2*m*Fin/(p*2^s) = 2*100*12/(3*2^1)=400M
	 */
	ldr r0, =0x4C000004
	ldr r1, =(92<<12)|(1<<4)|(1<<0)
	str r1, [r0]

	/* 一旦设置PLL, 就会锁定lock time直到PLL输出稳定
	 * 然后CPU工作于新的频率FCLK
	 */
	
	

	/* 设置内存: sp 栈 */
	/* 分辨是nor/nand启动
	 * 写0到0地址, 再读出来
	 * 如果得到0, 表示0地址上的内容被修改了, 它对应ram, 这就是nand启动
	 * 否则就是nor启动
	 */
	mov r1, #0
	ldr r0, [r1] /* 读出原来的值备份 */
	str r1, [r1] /* 0->[0] */ 
	ldr r2, [r1] /* r2=[0] */
	cmp r1, r2   /* r1==r2? 如果相等表示是NAND启动 */
	ldr sp, =0x40000000+4096 /* 先假设是nor启动 */
	moveq sp, #4096  /* nand启动 */
	streq r0, [r1]   /* 恢复原来的值 */
	

    bl sdram_init
    bl copy2sdram

    

    bl clean_bss
    ldr pc, =sdram
sdram:
    bl uart0_init

    bl print1
und_code:
    .word 0xdeadc0de
    bl print2

	//bl main
    ldr pc, =main

halt:
	b halt
