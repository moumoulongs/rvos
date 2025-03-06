#ifndef __SPINLOCK__
#define __SPINLOCK__

struct spinlock {
    uint32_t locked; //是否被使用

    // fot debugging:
    char *name; // 锁的名字
    struct cpu *cpu; // 锁的持有者
};



#endif /* __SPINLOCK__ */
