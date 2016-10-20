#include <pthread.h>
#include <stdio.h>

void *detachfun(void *arg) {
   int i = *((int *)(arg));
   if (!pthread_detach(pthread_self())) 
      return NULL;
   fprintf(stderr, "My argument is %d\n", i);
   return NULL;
}
LAGS (O_WRONLY | O_CREAT | O_TRUNC)

void *copyfilemalloc(void *arg);
 
int main (int argc, char *argv[]) { /* copy fromfile to tofile */
   int *bytesptr;
   int error; 
   int fds[2];
   pthread_t tid;
 
   if (argc != 3) {
      fprintf(stderr, "Usage: %s fromfile tofile\n", argv[0]);
      return 1;
   }
   if (((fds[0] = open(argv[1], READ_FLAGS)) == -1) ||
       ((fds[1] = open(argv[2], WRITE_FLAGS, PERMS)) == -1)) {
      perror("Failed to open the files");
      return 1;
   }
   if (error = pthread_create(&tid, NULL, copyfilemalloc, fds)) {
      fprintf(stderr, "Failed to create thread: %s\n", strerror(error));
      return 1;
   }
   if (error = pthread_join(tid, (void **)&bytesptr)) {
      fprintf(stderr, "Failed to join thread: %s\n", strerror(error));
      return 1;
   }
   printf("Number of bytes copied: %d\n", *bytesptr);
   return 0;
}
