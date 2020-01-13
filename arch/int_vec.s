// int_vec.s
// 
// Travis Banken
// 1/12/2020
// 
// Set up the interrupt vector

.section ".text"

.global move_exception_vector

// array of exception addr
// we load the address of the handler into pc (like a jump)
exception_vector_table:
    ldr     pc, reset_handler_abs_addr                      // 0x00
    ldr     pc, prefetch_abort_handler_abs_addr             // 0x04
    ldr     pc, software_interrupt_handler_abs_addr         // 0x08
    ldr     pc, data_abort_handler_abs_addr                 // 0x0c
    ldr     pc, undefined_instruction_handler_abs_addr      // 0x10
    nop // reserved                                         // 0x14
    ldr     pc, irq_handler_abs_addr                        // 0x18
    ldr     pc, fast_irq_handler_abs_addr                   // 0x1c

// define abs addr for all the handler addresses to get around -fpic flag
reset_handler_abs_addr:                 .word reset_handler
prefetch_abort_handler_abs_addr:        .word prefetch_abort_handler
software_interrupt_handler_abs_addr:    .word software_interrupt_handler
data_abort_handler_abs_addr:            .word data_abort_handler
undefined_instruction_handler_abs_addr: .word undefined_instruction_handler
irq_handler_abs_addr:                   .word irq_handler_asm_wrapper
fast_irq_handler_abs_addr:              .word fast_irq_handler



// moves the exception vector into addr 0x0000 as expected by ARM
move_exception_vector:
    push    {r4, r5, r6, r7, r8, r9} // preserve regs
    ldr     r0, =exception_vector_table
    mov     r1, #0x0000

    // mov the exception vector into addr 0x0000
    ldmia   r0!, {r2, r3, r4, r5, r6, r7, r8, r9}
    stmia   r1!, {r2, r3, r4, r5, r6, r7, r8, r9}
    // mov abs addr vals to same spot
    ldmia   r0!, {r2, r3, r4, r5, r6, r7, r8}
    stmia   r1!, {r2, r3, r4, r5, r6, r7, r8}

    pop     {r4, r5, r6, r7, r8, r9} // restore
    blx     lr

// wrapper around irq_handler with extra instructions, not provided by __atttribute__
irq_handler_asm_wrapper:
    // need to adjust return addr 1 instruction back because of arm quirk
    sub     lr, lr, #4

    // make life easier by switching back to supervisor mode (defaulted into IRQ mode)
    srsdb   sp!, #0x13
    cpsid   if, #0x13

    // need to save all registers since calling funct did not expect to be interrupted
    push    {r0-r3, r12, lr}

    // arm needs stack to be 8 aligned
    and     r1, sp, #4
    sub     sp, sp, r1

    // call irq_handler in interrupt.c
    bl      irq_handler

    // restore stack alignment
    add     sp, sp, r1

    // restore regs
    pop     {r0-r3, r12, lr}

    // restore cpsr and return
    rfeia   sp!
