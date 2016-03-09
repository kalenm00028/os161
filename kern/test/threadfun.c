#include <types.h>
#include <lib.h>
#include <thread.h>
#include <synch.h>
#include <test.h>

#define NTHREADS 8

int count = 0;
static struct semaphore *tsem = NULL;

/*Declare and intialize locks and create shared counter here*/

static
void
init_sem(void)
{
        if (tsem==NULL) {
                tsem = sem_create("tsem", 0);
                if (tsem == NULL) {
                        panic("threadtest: sem_create failed\n");
                }
        }
}

static void threadfuntest(void *junk, unsigned long num) {

	/*int ch = '0' + num;*/

	(void)junk;
	(void)num;

	for (int i = 0; i < 10000; i++) {
		count++;
	}

	kprintf("End count: %d \n", count);

	V(tsem);
}

static
void
runthreads(int input)
{
   char name[16];
   int i, result;

   for (i=0; i<=input; i++) {
      snprintf(name, sizeof(name), "threadtest%d\n", i);
      result = thread_fork(name, NULL,
                 threadfuntest,
                 NULL, i);
      if (result) {
         panic("threadtest: thread_fork failed %s)\n",
               strerror(result));
      }
   }

   for (i=0; i<=input; i++) {
      P(tsem);
   }

   kprintf("End count: %d \n", count);
}


int
threadfun(int nargs, char **args)
{
   (void)nargs;
   int input = *args[1] - 48;

   init_sem();
   kprintf("Starting unsafe counter test...\n");
   runthreads(input);
   kprintf("\nUnsafe counter test done.\n");

   return 0;
}
