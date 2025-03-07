        #
        # interrupts and exceptions while in supervisor
        # mode come here.
        #
        # the current stack is a kernel stack.
        # push registers, call kerneltrap().
        # when kerneltrap() returns, restore registers, return.
        #
.globl kerneltrap
.globl kernelvec
.align 4
kernelvec:
        # make room to save registers.
        addi sp, sp, -256

        # save caller-saved registers.
        sw ra, 0(sp)
        sw sp, 8(sp)
        sw gp, 16(sp)
        sw tp, 24(sp)
        sw t0, 32(sp)
        sw t1, 40(sp)
        sw t2, 48(sp)
        sw a0, 72(sp)
        sw a1, 80(sp)
        sw a2, 88(sp)
        sw a3, 96(sp)
        sw a4, 104(sp)
        sw a5, 112(sp)
        sw a6, 120(sp)
        sw a7, 128(sp)
        sw t3, 216(sp)
        sw t4, 224(sp)
        sw t5, 232(sp)
        sw t6, 240(sp)

        # call the C trap handler in trap.c
        call kerneltrap

        # restore registers.
        lw ra, 0(sp)
        lw sp, 8(sp)
        lw gp, 16(sp)
        # not tp (contains hartid), in case we moved CPUs
        lw t0, 32(sp)
        lw t1, 40(sp)
        lw t2, 48(sp)
        lw a0, 72(sp)
        lw a1, 80(sp)
        lw a2, 88(sp)
        lw a3, 96(sp)
        lw a4, 104(sp)
        lw a5, 112(sp)
        lw a6, 120(sp)
        lw a7, 128(sp)
        lw t3, 216(sp)
        lw t4, 224(sp)
        lw t5, 232(sp)
        lw t6, 240(sp)

        addi sp, sp, 256

        # return to whatever we were doing in the kernel.
        sret
