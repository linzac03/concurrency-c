#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
	pid_t childpid = 0; 
	int i, n, ii;

	if (argc != 4) {   /* check for valid number of command-line arguments */ 
		fprintf(stderr, "Usage: %s processes loops sleep\n", argv[0]);
		return 1; 
	}     
	n = atoi(argv[1]);  
	
	for (i = 1; i < n; i++)
		if (childpid = fork()) 
			break;
	
	for (ii = 0; ii<atoi(argv[2]); ii++) {
		sleep(atoi(argv[3])); 
		fprintf(stderr, "i:%d  process ID:%ld  parent ID:%ld  child ID:%ld\n",
			i, (long)getpid(), (long)getppid(), (long)childpid);
	}
	return 0; 
}
