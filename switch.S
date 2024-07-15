#define SIZE_REG 4

# 将寄存器信息保存到 base 中
.macro reg_save base
    sw ra,   0*SIZE_REG(\base)
    sw sp,   1*SIZE_REG(\base)
    sw t0,   4*SIZE_REG(\base)
    sw t1,   5*SIZE_REG(\base)
    sw t2,   6*SIZE_REG(\base)
    sw s0,   7*SIZE_REG(\base)
    sw s1,   8*SIZE_REG(\base)
    sw a0,   9*SIZE_REG(\base)
    sw a1,   10*SIZE_REG(\base)
    sw a2,   11*SIZE_REG(\base)
    sw a3,   12*SIZE_REG(\base)
    sw a4,   13*SIZE_REG(\base)
    sw a5,   14*SIZE_REG(\base)
    sw a6,   15*SIZE_REG(\base)
    sw a7,   16*SIZE_REG(\base)
    sw s2,   17*SIZE_REG(\base)
    sw s3,   18*SIZE_REG(\base)
    sw s4,   19*SIZE_REG(\base)
    sw s5,   20*SIZE_REG(\base)
    sw s6,   21*SIZE_REG(\base)
    sw s7,   22*SIZE_REG(\base)
    sw s8,   23*SIZE_REG(\base)
    sw s9,   24*SIZE_REG(\base)
    sw s10,  25*SIZE_REG(\base)
    sw s11,  26*SIZE_REG(\base)
    sw t3,   27*SIZE_REG(\base)
    sw t4,   28*SIZE_REG(\base)
    sw t5,   29*SIZE_REG(\base)
.endm

#从 base 中读取
.macro reg_restore base
	lw ra,   0*SIZE_REG(\base)
	lw sp,   1*SIZE_REG(\base)
	lw t0,   4*SIZE_REG(\base)
	lw t1,   5*SIZE_REG(\base)
	lw t2,   6*SIZE_REG(\base)
	lw s0,   7*SIZE_REG(\base)
	lw s1,   8*SIZE_REG(\base)
	lw a0,   9*SIZE_REG(\base)
	lw a1,  10*SIZE_REG(\base)
	lw a2,  11*SIZE_REG(\base)
	lw a3,  12*SIZE_REG(\base)
	lw a4,  13*SIZE_REG(\base)
	lw a5,  14*SIZE_REG(\base)
	lw a6,  15*SIZE_REG(\base)
	lw a7,  16*SIZE_REG(\base)
	lw s2,  17*SIZE_REG(\base)
	lw s3,  18*SIZE_REG(\base)
	lw s4,  19*SIZE_REG(\base)
	lw s5,  20*SIZE_REG(\base)
	lw s6,  21*SIZE_REG(\base)
	lw s7,  22*SIZE_REG(\base)
	lw s8,  23*SIZE_REG(\base)
	lw s9,  24*SIZE_REG(\base)
	lw s10, 25*SIZE_REG(\base)
	lw s11, 26*SIZE_REG(\base)
	lw t3,  27*SIZE_REG(\base)
	lw t4,  28*SIZE_REG(\base)
	lw t5,  29*SIZE_REG(\base)
	lw t6,  30*SIZE_REG(\base)
.endm

.text

.globl switch_to
.balign 4
switch_to:
    csrw	mscratch, a0
	lw      a1, 31*SIZE_REG(a0)
	csrw	mepc, a1
	mv	t6, a0
	reg_restore t6
    mret

.globl trap_vector
.balign 4
trap_vector:
    #store context
    csrrw   t6, mscratch, t6
    reg_save t6
    mv  t5, t6
    csrr    t6, mscratch
    sw      t6, 30*SIZE_REG(t5)
    csrr    a0, mepc
    sw      a0, 31*SIZE_REG(t5)

    #store context into mscratch
    csrw    mscratch, t5

    #call trap_handler   reg_t trap_handler(reg_t epc, reg_t cause)
    csrr    a0, mepc
    csrr    a1, mcause
    call    trap_handler
    csrw    mepc, a0

    #restore context from mscratch
    csrr    t6, mscratch
    reg_restore t6

    #return
    mret

.end
    