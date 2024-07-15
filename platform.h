#ifndef __PLATFORM_H__
#define __PLATFORM_H__

/*
 * QEMU RISC-V Virt machine with 16550a UART and VirtIO MMIO
 */

/*
 * maximum number of CPUs
 * see https://github.com/qemu/qemu/blob/master/include/hw/riscv/virt.h
 * #define VIRT_CPUS_MAX 8
 */
#define MAXNUM_CPU 8

/* used in os.ld */
#define LENGTH_RAM 128*1024*1024
#define KERNBASE 0x80000000L

/*
 * MemoryMap
 * see https://github.com/qemu/qemu/blob/master/hw/riscv/virt.c, virt_memmap[]
 * 0x00001000 -- boot ROM, provided by qemu
 * 0x02000000 -- CLINT
 * 0x0C000000 -- PLIC
 * 0x10000000 -- UART0
 * 0x10001000 -- virtio disk
 * 0x80000000 -- boot ROM jumps here in machine mode, where we load our kernel
 */

/* This machine puts UART registers here in physical memory. */
#define UART0 0x10000000L

/* UART0 中断源号 */
#define UART0_IRQ 10

/* PLIC设备 */
#define PLIC_BASE 0x0c000000L

#define PLIC_PRIORITY(id) (PLIC_BASE + (id) * 4) /*寄存器地址*/
#define PLIC_PENDING(id) (PLIC_BASE + 0x1000 + ((id) / 32) * 4) /*中断是否发生*/
#define PLIC_MENABLE(hart, id) (PLIC_BASE + 0x2000 + (hart) * 0x80 + ((id) / 32) * 4) /*是否开始该中断源*/
#define PLIC_MTHRESHOLD(hart) (PLIC_BASE + 0x200000 + (hart) * 0x1000) /*中断源优先级阈值*/
/*操作同一个寄存器 读为claim 写为complete*/
#define PLIC_MCLAIM(hart) (PLIC_BASE + 0x200004 + (hart) * 0x1000) /*获取当前发生的最高优先级中断源ID， 成功后清楚对应pending位*/
#define PLIC_MCOMPLETE(hart) (PLIC_BASE + 0x200004 + (hart) * 0x1000) /*通知PLIC对该路中断的处理已经结束*/


/*内存末地址*/
#define PHYSTOP (KERNBASE + 128*1024*1024)

/* CLINT设备 */
#define CLINT_BASE 0x2000000L
#define CLINT_MSIP(hartid) (CLINT_BASE + 4 * (hartid))
#define CLINT_MTIMECMP(hartid) (CLINT_BASE + 0x4000 + 8 * (hartid))
#define CLINT_MTIME (CLINT_BASE + 0xBFF8) // cycles since boot.

#endif /* __PLATFORM_H__ */
