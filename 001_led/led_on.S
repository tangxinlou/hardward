 /*
 * 点亮LED1: gpf4
 */

 .text
 .global _start

 _start:
 
/*
 * 点亮LED1: gpf4
 */
    ldr r1, =0x56000050
    ldr r0, =0x100 /* mov r0, #0x100 */
    str r0, [r1]
    
    ldr r1, =0x56000054
    ldr r0, =0 /* mov r0, #0 */
    str r0, [r1]

halt:
    b halt

