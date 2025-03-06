#include "types.h"
#include "param.h"
#include "platform.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "os.h"

void initlock(struct spinlock *lk, char *name)
{
    lk->name = name;
    lk->locked = 0;
    lk->cpu = 0;
}

// 获取锁
// 如果锁已经被占用，自旋等待
void acquire(struct spinlock *lk)
{
    push_off(); //关中断
    if(holding(lk)) //检查是否已经持有锁
    {
        panic("acquire");
    }

    // 自旋直到锁被释放
    while(__sync_lock_test_and_set(&lk->locked, 1) != 0)
        ;

    // 内存屏障，告诉编译器不要对内存操作进行优化，使锁的获取在资源的操作之前进行
    __sync_synchronize();

    // 记录锁的持有者
    lk->cpu = mycpu();
}

// 释放锁
void release(struct spinlock *lk)
{
    if(!holding(lk))
    {
        panic("release");
    }

    lk->cpu = 0;

    // 内存屏障，告诉编译器不要对内存操作进行优化，使锁的释放在资源的操作之后进行
    __sync_synchronize();

    // 释放锁
    __sync_lock_release(&lk->locked);

    pop_off(); //开中断
}

// 检查当前CPU是否持有该锁
int holding(struct spinlock *lock)
{
    int r;
    push_off();
    r = lock->locked && lock->cpu == mycpu();
    pop_off();
    return r;
}

// 关中断 , 使用了多少次push_off()就要使用多少次pop_off()来开中断

void push_off(void)
{
    int old = intr_get();
    
    intr_off();
    if(mycpu()->noff == 0)
        mycpu()->intena = old;
    mycpu()->noff += 1;
}

// 开中断

void pop_off(void)
{
    struct cpu *c = mycpu();
    if(intr_get())
        panic("pop_off - interruptible");
    if(c->noff < 1)
        panic("pop_off");
    c->noff -= 1;
    if(c->noff == 0 && c->intena)
        intr_on();
}