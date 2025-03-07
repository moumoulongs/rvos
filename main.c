#include "os.h"

/*
 * Following functions SHOULD be called ONLY ONE time here,
 * so just declared here ONCE and NOT included in file os.h.
 */
extern void uart_init(void);
extern void kinit(void);



void main(void)
{

	printf("Hello, RISC-V!\n");

}

