#include "os.h"

/*
 * Following functions SHOULD be called ONLY ONE time here,
 * so just declared here ONCE and NOT included in file os.h.
 */
extern void uart_init(void);
extern void kinit(void);



void main(void)
{
    printf("\n");
    printf("kernel is booting\n");
    printf("\n");
    kinit();         // physical page allocator
    procinit();      // process table
    trapinit();      // trap vectors
    trapinithart();  // install kernel trap vector
    plicinit();      // set up interrupt controller
    plicinithart();  // ask PLIC for device interrupts
    // userinit();      // first user process

	while (1)
	{
		int pid = fork();
		if (pid == 0)
		{
			printf("child\n");
		}
		else
		{
			printf("parent\n");
		}
	}

}

