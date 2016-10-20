#include <stdio.h>
#include "waitatbarrier.c"

int i;
volatile int ret = 0;
pid_t childpid;
char *bname;

int main(int argc, char **argv) {	
	if (argc != 2) {
		printf("Usage barrierclient [barrier]\n");
		return 0;
	}
	printf("Client started..\n");

	bname = argv[1];
	ret = waitatbarrier(bname);

	printf("..Client exited\n");
}
