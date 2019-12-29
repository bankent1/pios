@ Travis Banken
@
@ AArch32 mode boot


.section ".text.boot"

.global _start

_start:
    @ Comment out to use all cores
    @ -----------------------------------------------
    @ tell all but core 0 to halt (shut down other)
    mrc p15, #0, r1, c0, c0, #5
    and r1, r1, #3
    cmp r1, #0
    bne boot_halt
    @ -----------------------------------------------


    @ set up stack
    mov sp, #0x8000 @ 32AArch specific

    @ clear out bss
    ldr r4, =__bss_start    @ load bss start into r4
    ldr r9, =__bss_end      @ load bss end into r9
    mov r5, #0
    mov r6, #0
    mov r7, #0
    mov r8, #0

@ loop to zero out bss section
boot_loop:
    stmia r4!, {r5-r8}      @ store whats in r5-r8 then increment r4 pointer

    cmp r4, r9
    blo boot_loop

    @ load kernel
    ldr r3, =kernel_main
    blx r3

boot_halt:
    @ enter low power state and loop
    wfe
    b boot_halt

