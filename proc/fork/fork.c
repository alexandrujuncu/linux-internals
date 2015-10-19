#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	/* Code ran by the parent. */
	printf("Process %d started\n", getpid());

	/* TODO 2: Toggle to set an environment variable. */
	#if 0
	setenv("FOO", "BAR", 0);
	#endif

	/* Fork the current process. */
	pid_t pid = fork();

	/* Check if fork succeeded. Maybe we have some limits. */
	if (pid < 0) {
		printf("Error while forking.\n");
		return -1;
	}

	/* Who am I? */
	if (pid == 0 ) {
		/* Code ran by the child. */
		printf("I am a baby process and my pid is %d \n.", getpid());

		/* TODO 1: Togle this #if to also call exec() */
		#if 0
		execvp("bash", NULL);
		#endif
	}
	else {
		/* Code ran by the parent. */
		printf("I am a proud parent of process %d. I still have the pid %d \n.", pid, getpid());
	}

	/* Core ran by both processes. */
	printf("Press CTRL+C to stop us.\n");

	while(1) {
		printf("%d: ZZZzzz\n", getpid());
		sleep(5);
	}

	return 0;
}
