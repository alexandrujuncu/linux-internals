#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signum)
{
	printf("RINGRING!\n");
}

int main(void)
{

	printf("Process %d started\n", getpid());

	/* TODO: Toogle #if to enable signal handling. */
#if 0
	if(signal(SIGHUP, signal_handler) == SIG_ERR) {
		printf("Unable to catch SIGHUP");
		exit(EXIT_FAILURE);
	}
#endif

	printf("Press CTRL+C to stop us\n");

	while(1) {
		sleep(1);
	}

	return 0;
}
