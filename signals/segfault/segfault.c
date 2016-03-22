#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void signal_handler(int signum)
{
	printf("Oh noes, a seg fault!\n");
	exit(1);
}



int main (void)
{
	/* TODO: Toogle #if to enable SEGSEGV handling. */
#if 0
	if(signal(SIGSEGV, signal_handler) == SIG_ERR) {
		printf("Unable to catch SIGSEGV");
		exit(EXIT_FAILURE);
	}
#endif

	int *p;		/* Define a pointer. */
	p = 0;		/* Point it to the address 0. */

	*p = 42;	/* Watch the world burn. */

	return 0;
}

