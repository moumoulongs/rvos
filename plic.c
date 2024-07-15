#include "os.h"

void plic_init()
{
    
    int hart = r_tp(); /* 访问当前线程的 TCB */
    *(uint32_t*)PLIC_PRIORITY(UART0_IRQ) = 1; /* 设置优先级 */
    *(uint32_t*)PLIC_MENABLE(hart, UART0_IRQ)= (1 << (UART0_IRQ % 32)); /* 开启UART0设备中断 */
    *(uint32_t*)PLIC_MTHRESHOLD(hart) = 0; /* 阈值设置为0 */
    
    w_mie(r_mie() | MIE_MEIE); /* 开启M级外部中断 */
    w_mstatus(r_mstatus() | MSTATUS_MIE); /* 开启全局中断 */
}

/* 获取中断源ID */
int plic_claim(void)
{
    int hart = r_tp();
    int irq = *(uint32_t*)PLIC_MCLAIM(hart);
    return irq;
}

/* 完成中断 */
void plic_complete(int irq)
{
    int hart = r_tp();
    *(uint32_t*)PLIC_MCOMPLETE(hart) = irq;
}