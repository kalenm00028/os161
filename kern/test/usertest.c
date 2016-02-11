#include <types.h>
#include <lib.h>
#include <test.h>

int usertest(int argc, char *argv[]) {

	int i;

	for (i = 1; i < argc; i++) {
		kprintf("%s ", argv[i]);
	}

	kprintf("\n");

	return 0;

}
