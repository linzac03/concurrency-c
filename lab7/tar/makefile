#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *processfd(void *arg);

void monitorfd(int fd[], int numfds) {       /* create threads to monitor fds */
   int error, i;
   pthread_t *tid;
    
   if ((tid = (pthread_t *)calloc(numfds, sizeof(pthread_t))) == NULL) {
      perror("Failed to allocate space for thread IDs");
      return;
   }
   for (i = 0; i < numfds; i++)   /* create a thread for each file descriptor */
      if (error = pthread_create(tid + i, NULL, processfd, (fd + i))) {
         fprintf(stderr, "Failed to create thread %d: %s\n",
                         i, strerror(error));
         tid[i] = pthread_self();
      }
   for (i = 0; i < numfds; i++) {
      if (pthread_equal(pthread_self(), tid[i]))
         continue;
      if (error = pthread_join(tid[i], NULL))
         fprintf(stderr, "Failed to join thread %d: %s\n", i, strerror(error));
   }
   free(tid);
   return;
}
restart.c $(LIBTHREAD)

copymultiple: copymultiple.c copyfilepass.c restart.c
	$(CC) $(COPS) -o copymultiple copymultiple.c copyfilepass.c restart.c $(LIBTHREAD)

badparameters: badparameters.c
	$(CC) $(COPS) -o badparameters badparameters.c $(LIBTHREAD)

makeprioritytest: makeprioritytest.c
	$(CC) $(COPS) -o makeprioritytest makeprioritytest.c makepriority.c $(LIBTHREAD)

lintall: lintmonitorfd lintmonitorfdcancel lintdetachfun lintcallcopymalloc lintcallcopypass lintcopymultiple lintbadparameters lintwhichexit lintmakepriority

lintmonitorfd:
	$(LINT) $(LOPS) monitorfd.c processfd.c restart.c 

lintmonitorfdcancel:
	$(LINT) $(LOPS) monitorfdcanceltest.c monitorfdcancel.c processfdcancel.c restart.c 

lintdetachfun:
	$(LINT) $(LOPS) detachfuntest.c detachfun.c

lintcallcopymalloc:
	$(LINT) $(LOPS) callcopymalloc.c copyfilemalloc.c restart.c

lintcallcopypass:
	$(LINT) $(LOPS) callcopypass.c copyfilepass.c restart.c

lintcopymultiple:
	$(LINT) $(LOPS) copymultiple.c copyfilepass.c restart.c

lintbadparameters:
	$(LINT) $(LOPS) badparameters.c

lintwhichexit:
	$(LINT) $(LOPS) whichexit.c

lintmakepriority:
	$(LINT) $(LOPS) makeprioritytest.c makepriority.c

clean:
	rm -f *.o core pipe1 pipe2 monitorfdtest detachfuntest monitorfdcanceltest copymultiple callcopymalloc callcopypass badparameters makeprioritytest
