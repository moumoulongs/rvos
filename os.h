#ifndef __OS_H__
#define __OS_H__

#include "types.h"
#include "riscv.h"
#include "platform.h"

#include <stddef.h>
#include <stdarg.h>

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

#endif /* __OS_H__ */
