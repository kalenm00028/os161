#include <types.h>
#include <lib.h>
#include <thread.h>
#include <synch.h>
#include <test.h>

#define NTHREADS 8

static struct lock* count_lock;
static struct semaphore *tsem = NULL;

int countB = 0;

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

	(void)num;

	for (int i = 0; i < 10000; i++) {
		spinlock_acquire(&count_lock->lk_spinlock);
		countB++;
		spinlock_release(&count_lock->lk_spinlock);
	}

	(void)junk;
	V(tsem);
}

static
void
runthreads(int input)
{
   char name[16];
   int i, result;
   int number = input;

   for (i=0; i<number; i++) {
      snprintf(name, sizeof(name), "threadtest%d\n", i);
      result = thread_fork(name, NULL,
                 threadfuntest,
                 NULL, i);
      if (result) {
         panic("threadtest: thread_fork failed %s)\n",
               strerror(result));
      }
   }

   for (i=0; i<number; i++) {
      P(tsem);
   }

   kprintf("End count: %d \n", countB);
}


int
spinLockCounter(int nargs, char *args[])
{
   (void)nargs;
   int input = *args[1] - 48;

   init_sem();
   kprintf("Starting Spin Lock counter test...\n");
   count_lock = lock_create(" ");
   runthreads(input);
   kprintf("\nSpin Lock counter test done.\n");

   return 0;
}
