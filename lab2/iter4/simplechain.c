#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
	pid_t childpid = 0; 
	int i, n, ii;

	if (argc != 3) {   /* check for valid number of command-line arguments */ 
		fprintf(stderr, "Usage: %s processes loops\n", argv[0]);
		return 1; 
	}     
	n = atoi(argv[1]);  
	
	for (i = 1; i < n; i++)
		if (childpid = fork()) 
			break;
	
	for (ii = 0; ii<atoi(argv[2]); ii++) {
		wait();
		fprintf(stderr, "i:%d ", i);
		fprintf(stderr, "process ID:%ld ", (long)getpid());
		fprintf(stderr, "parent ID:%ld ", (long)getppid());
		fprintf(stderr, "child ID:%ld\n", (long)childpid);
	}
	return 0; 
}
