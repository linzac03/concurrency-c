#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
	pid_t childpid = 0; 
	char *mybuf = (char *)malloc(atoi(argv[3])*sizeof(char));
	char *tmp;	
	int i, n, ii;

	if (argc != 4) {   /* check for valid number of command-line arguments */ 
		fprintf(stderr, "Usage: %s processes nloops nchars\n", argv[0]);
		return 1; 
	}     
	n = atoi(argv[1]);  
	
	for (i = 1; i < n; i++)
		if (childpid = fork()) 
			break;
	
	for (ii = 0; ii<atoi(argv[2]); ii++) {
		wait();
		for (i = 0; i<atoi(argv[3]); i++) {
			mybuf[i] = getchar();
		}
		mybuf[i] = '\0';
		fprintf(stderr, "process ID:%ld | %s", (long)getpid(), mybuf);
	}
	return 0; 
}
