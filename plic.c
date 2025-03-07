#include "types.h"
#include "param.h"
#include "platform.h"
#include "riscv.h"
#include "os.h"

void plicinit(void)
{
    // UART0和virtio disk的中断使能设置为1
    *(uint32_t*)(PLIC + UART0_IRQ * 4) = 1;
    *(uint32_t*)(PLIC + VIRTIO0_IRQ * 4) = 1;
}

void plicinithart(void)
{
    int hart = cpuid();

    //设置当前处理器的 S-mode ，启用uart和virtio disk中断
    *(uint32_t*)PLIC_SENABLE(hart) = (1 << UART0_IRQ) | (1 << VIRTIO0_IRQ);

    //设置当前处理器的 S-mode ，设置优先级阈值为0
    *(uint32_t*)PLIC_SPRIORITY(hart) = 0;
}

// 获取中断源号
int plic_claim(void)
{
    int hart = cpuid();
    int irq = *(uint32_t*)PLIC_SCLAIM(hart);
    return irq;
}

/* 完成中断 */
void plic_complete(int irq)
{
    int hart = cpuid();
    *(uint32_t*)PLIC_SCLAIM(hart) = irq;
}