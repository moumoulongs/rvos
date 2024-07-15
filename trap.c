#include "os.h"

extern reg_t trap_vector(void);
extern void timer_handle(void);

void trap_init(void)
{
    w_mtvec((reg_t)trap_vector);
    plic_init();
    timer_init();
}

/* trap */
reg_t trap_handler(reg_t epc, reg_t cause)
{
    reg_t return_pc = epc;
    reg_t cause_code = cause&MCAUSE_MASK_ECODE;
    
    //cause最高位  1：中断  0：异常
    if(cause&MCAUSE_MASK_INTERRUPT) // 中断
    {
        switch(cause_code)
        {
            case 3: /* M软终端 */
			    uart_puts("software interruption!\n");
                int id = r_mhartid();
                *(uint32_t*)CLINT_MSIP(id) = 0;
			    break;
		    case 7: /* M时间中断 */
                // printf("timer intrupt\n");
			    timer_handle();
			    break;
            case 11: /* M外设中断 */
                uart_puts("external interruption!\n");
                external_interrupt_handler();
                break;
            default:
                printf("Unknown interruption! Code = %ld\n", cause_code);
			    break;
        }
    } else { // 异常
        /* Synchronous trap - exception */
		printf("Sync exceptions! Code = %ld\n", cause_code);
        printf("error at %p\n",epc);
		panic("OOPS! What can I do!");
		// return_pc += 4;
    }

    return return_pc;
}

/* 外部中断*/
void external_interrupt_handler(void)
{
    int irq = plic_claim();
    switch(irq)
    {
        case UART0_IRQ:
            uart_isr();
            plic_complete(irq);
        break;
        default:
            printf("unexpected interrupt irq = %d\n", irq);
        break;
    }
}