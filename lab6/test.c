#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv){
	int i;
	for (i=0; i<strlen(argv[1]); i++)
		write(STDOUT_FILENO, argv[1], 1);
}
