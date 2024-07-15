#include "os.h"

/* 100ms */
#define TIMER_INTERVAL 1000000

/* interval tick 后触发中断 */
void timer_load(int interval)
{
    /* 每个hart有独立的时间中断 */
    int id = r_mhartid();

    *(uint64_t*)CLINT_MTIMECMP(id) = *(uint64_t*)CLINT_MTIME + interval;

}

void timer_init(void)
{
    timer_load(TIMER_INTERVAL);

    /* 启动时间中断 */
    w_mie(r_mie() | MIE_MTIE);
}

void timer_handle(void)
{
    /* 设置下次时间中断间隔 100ms */
    timer_load(TIMER_INTERVAL);

    /* 时间中断处理 */
    schedule();
    
}
