#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

int main(int argc, char **argv) {
	int pr_limit;
	int pr_count = 0;
	char str[MAX_CANON];
	char** myargs;
	pid_t child_id;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s processes", argv[0]);
		return 1;
	}
	
	if (atoi(argv[1]) <= 0) {
		fprintf(stderr, "Needs at least 1: you enter %d", atoi(argv[1]));
		return 1;
	}

	pr_limit = atoi(argv[1]);

	for(; ;){
		if ((fgets(str, MAX_CANON, stdin)) == NULL) break;
	
		if (pr_count == pr_limit) {
			r_wait(NULL);
			pr_count--;
		}	
		
		if ((child_id = fork()) == 0) {
			fprintf(stdout, "CMD: %s", str);
			pr_count++;
			makeargv(str, " \t\n", &myargs);
			execvp(myargs[0], &myargs[0]);
			perror("Child didn't exec");
		} else if (child_id != r_wait(NULL)){
			perror("Parent failed to wait");
			break;
		} 	
	}
	
	while(pr_count > 0) {
		//r_wait(NULL);
		pr_count--;
	}
	return 0;
}
