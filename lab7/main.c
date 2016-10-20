#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
//#include "copydirectory.c"

void *copydirectory(void *arg);

int main(int argc, char **argv) {
	char *tmp;
	int error;
	int *bytesptr;
	pthread_t tid;
	
	if (argc != 3) {
		printf("Usage copydirectory [fromdir] [todir]\n");
	}
	tmp = malloc(sizeof(argv[1])+sizeof(argv[2])+2);
	strcat(tmp,argv[1]);
	strcat(tmp,"|");
	strcat(tmp,argv[2]);
	if (error = pthread_create(&tid, NULL, copydirectory, tmp)) {
  	fprintf(stderr, "Failed to create thread: %s\n", strerror(error));
  	return 1;
	}
	
	if (error = pthread_join(tid, (void **)NULL)) {
		fprintf(stderr, "Failed to join thread: %s\n", strerror(error));
		return 1;
	}
	return 0;
}
