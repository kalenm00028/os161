/*
 * An example program.
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

int
main()
{
	//reboot(RB_POWEROFF);
	printf("Beginning Stubtest\n");

	int pid1;
	int pid2;

	pid1 = getpid();

	printf("getpid: %d\n", pid1);

	pid2 = 5;
	int status;
	printf("waitpid: %d\n", waitpid(pid2, &status, 0));

	pid_t pid;
	pid = fork();
	if(pid > 0) {
		printf("I am a parent\n");
	}
	else {
		printf("I am a child\n");
	}


	_exit(0);
}
