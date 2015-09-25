#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


/* Break function to be included in the code to give time make
 * observations. Can be deactivated by #if 0 */
#if 1
	#define BREAK do { \
		printf("Taking a break. Press Enter to continue.\n"); \
		getchar(); \
	} while (0)
#else
#define BREAK do { \
} while (0)
#endif

/* Function that writes a buffer to a file(fd) */
int write_buffer(int fd, const char* buffer)
{

	int to_write = strlen(buffer);
	int written = 0;

	/* Never ever EVER asume that the buffer will be written in one go */
	while (written < to_write) {
		int ret;
		ret = write(fd, buffer + written, to_write);
		if (ret) {
			if (ret > 0) {
				to_write -= ret;
				written += ret;
			}
			else
				printf("Error writing buffer\n");
				return -1;
		}
		else
			break;
	}

	return 0;
}

int main(void)
{
	printf("Process %d started\n", getpid());

	BREAK;

	/* Open file as fd1 */
	int fd1 = open("rick.txt", O_RDWR | O_CREAT, 0644);
	if (fd1 < 0) {
		printf("Error opening file for fd1\n");
		return -1;
	}

	BREAK;

	printf("File opened with fd1=%d\n", fd1);

	/* Do some writes into the file via fd1 */
	write_buffer(fd1, "Never gonna give you up.\n");


	BREAK;

	write_buffer(fd1, "Never gonna let you down.\n");


	BREAK;


	/* Duplicate fd1 into fd1 */
	int fd2 = dup(fd1);

	printf("Duplicate fd1 into fd2=%d\n", fd2);


	BREAK;

	/* Do some writes into the file via fd2 */
	write_buffer(fd2, "Never gonna run around\n");

	BREAK;

	/* Do some more writes into the file via fd1 */
	write_buffer(fd1, ".. and desert you.\n");

	BREAK;



	/* Open the same file again as fd3 */
	int fd3 = open("rick.txt", O_RDWR | O_CREAT, 0644);
	if (fd3 < 0) {
		printf("Error opening file for fd3\n");
		return -1;
	}

	printf("File opened with fd3=%d\n", fd3);


	BREAK;

	/* Do some writes into the file via fd3 */
	write_buffer(fd3, "LAMA");


	BREAK;


	/* Do some more writes into the file via fd1 and fd2 */
	write_buffer(fd1, "Never gonna give\n");

	BREAK;

	write_buffer(fd2, "Never gonna give\n");

	BREAK;

	/* Do some more writes into the file via fd3 */
	write_buffer(fd3, " out of nowhere!");

	BREAK;


	return 0;
}
