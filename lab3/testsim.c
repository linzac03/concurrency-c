#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char **argv) {
	int i;	
	
	if (argc != 3) {
		fprintf(stderr, "Usage: %s [sleep] [repeat]", argv[0]);
	}
	
	for(i=0; i<atoi(argv[2]); i++) {
		sleep(atoi(argv[1]));
		fprintf(stdout, "My name is %ld \n", (long)getpid());
	}
	
	return 0;
}
