#ifndef __OS_H__
#define __OS_H__

#include "types.h"
#include "riscv.h"
#include "platform.h"

#include <stddef.h>
#include <stdarg.h>

struct buf;
struct context;
struct file;
struct inode;
struct pipe;
struct proc;
struct spinlock;
struct sleeplock;
struct stat;
struct superblock;


/* uart */
extern int uart_putc(char ch);
extern void uart_puts(char *s);
extern void uart_isr(void);

/* printf */
extern int  printf(const char* s, ...);
extern void panic(char *s);

/* memory management */
extern void kinit();
extern void *kalloc(void);
extern void kfree(void *pa);

/* string.c */
extern int memcmp(const void*, const void*, uint32_t);
extern void *memmove(void*, const void*, uint32_t);
extern void *memset(void*, int, uint32_t);
extern char *safestrcpy(char*, const char*, int);
extern int strlen(const char*);
extern int strncmp(const char*, const char*, uint32_t);
extern char *strncpy(char*, const char*, int);

/* task management */
void sched_init();
extern int  task_create(void (*task)(void));
extern void task_delay(volatile int count);

/* trap management */
void trap_init(void);
void external_interrupt_handler(void);

/* plic management */
void plic_init(void);
int plic_claim(void);
void plic_complete(int irq);

/* sched management */
void sched_init(void);
void schedule(void);

/* timer management */
void timer_init(void);

/* spinlock.c */
void acquire(struct spinlock*);
int holding(struct spinlock*);
void initlock(struct spinlock*, char*);
void release(struct spinlock*);
void push_off(void);
void pop_off(void);

// swtch.S
void            swtch(struct context*, struct context*);

// proc.c
int             cpuid(void);
void            exit(int);
int             fork(void);
int             growproc(int);
int             kill(int);
int             killed(struct proc*);
void            setkilled(struct proc*);
struct cpu*     mycpu(void);
struct cpu*     getmycpu(void);
struct proc*    myproc();
void            procinit(void);
void            scheduler(void) __attribute__((noreturn));
void            sched(void);
void            sleep(void*, struct spinlock*);
void            userinit(void);
int             wait(uint64_t);
void            wakeup(void*);
void            yield(void);
int             either_copyout(int user_dst, uint64_t dst, void *src, uint64_t len);
int             either_copyin(void *dst, int user_src, uint64_t src, uint64_t len);
void            procdump(void);

#endif /* __OS_H__ */
