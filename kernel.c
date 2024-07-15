#include "os.h"

/*
 * Following functions SHOULD be called ONLY ONE time here,
 * so just declared here ONCE and NOT included in file os.h.
 */
extern void uart_init(void);
extern void kinit(void);

void task1(void)
{
	printf("create task1\n");
	while(1)
	{
		printf("this is task 1\n");
		task_delay(1000);
	}
}

void task2(void)
{
	printf("create task2\n");
	while(1)
	{
		printf("this is task 2\n");
		task_delay(1000);
	}
}


void start_kernel(void)
{
	
	uart_init();
	kinit();
	trap_init();
	sched_init();
	uart_puts("Hello, RVOS!\n");
	printf("OK\n");

	task_create(task1);
	task_create(task2);
	schedule();
	while (1) {}; // stop here!
}

