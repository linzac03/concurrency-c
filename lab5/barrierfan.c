#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "restart.h"
#define FIFOARG 1
#define FIFO_PERMS (S_IRWXU | S_IWGRP| S_IWOTH)

int main  (int argc, char *argv[]) {
	char reqbuf[256];
	char relbuf[] = "g";
	char *req;
	char *rel;
	int reqfd, relfd; 
	pid_t childpid = 0;
	int fd[2]; 
	int i, n;

	if (argc != 3){
		/* check for valid number of command-line arguments */
		fprintf (stderr, "Usage: %s name processes\n", argv[0]);
		return 1;
	}

	n = atoi(argv[2]);
	req = malloc(sizeof(char)*(strlen(argv[FIFOARG])+10));
	rel = malloc(sizeof(char)*(strlen(argv[FIFOARG])+10));
	strcpy(req,argv[FIFOARG]);
	strcpy(rel,argv[FIFOARG]);
	strcat(req,".request");
	strcat(rel,".release");

	if ((mkfifo(req, FIFO_PERMS) == -1) && (errno != EEXIST)) {
		perror("Failed to create the request FIFO");
		return 1;
	}

	if ((mkfifo(rel, FIFO_PERMS) == -1) && (errno != EEXIST)) {
		perror("Failed to create the release FIFO");
		return 1;
	}

	while(1) {
		if ((reqfd = open(req, O_RDWR)) == -1) {
			perror("Server Failed to open request FIFO");
		}

		for (i=0; i < n; i++) {
			if (read(reqfd, reqbuf, 1) == -1) {
				perror("Server Failed to read from request");
			}
			write(STDOUT_FILENO, reqbuf, 1);
		}

		if (reqfd > 0)
			close(reqfd);
	
		if ((relfd = open(rel, O_WRONLY)) == -1)
			perror("Server Failed to open release FIFO");
		for (i = 0; i < n; i++) {
			if (write(relfd, relbuf, 1) == -1) {
				perror("Server Failed to write synchronization characters");
			}
			write(STDOUT_FILENO, relbuf, 1);
		}
	
		if (relfd > 0)
			close(relfd);	
	}
	free(rel);
	free(req);
	return (childpid == -1);
}
