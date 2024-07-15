#include "proc.h"
#include "os.h"

extern void switch_to(struct context *next);

#define MAX_TASK 10
#define STACK_SIZE 1024

uint8_t __attribute__((aligned(16))) task_stack[MAX_TASK][STACK_SIZE];
struct context ctx_tasks[MAX_TASK];

static int _top = 0;
static int _current = -1;


void sched_init() // 初始化
{
    w_mscratch(0);

    /* 启用软中断 */
    w_mie(r_mie() | MIE_MSIE);
}

void schedule() //n轮换
{
    if(_top <= 0) {
        panic("schedule");
        return;
    }

    _current = (_current + 1) % _top;
    struct context *next = &ctx_tasks[_current];
    switch_to(next);
}

int task_create(void(*start_routin)(void)) // 创建作业
{
    if(_top < MAX_TASK) {
        ctx_tasks[_top].sp = (reg_t) &task_stack[_top][STACK_SIZE];
        ctx_tasks[_top].mepc = (reg_t) start_routin;
        _top++;
        return 0;
    } else {
        return -1;
    }
}

/* 协作式多任务 修改switch_to */
// void task_yield()
// {
//     schedule();
// }

void task_delay(volatile int count)
{
    count *= 50000;
    while (count--);
}

