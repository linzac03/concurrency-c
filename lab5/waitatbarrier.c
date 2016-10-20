#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "restart.h"
#define REQUEST 0
#define RELEASE 1
#define FIFOARG 1
#define FIFO_PERMS (S_IRWXU | S_IWGRP| S_IWOTH)

int waitatbarrier(char *name) {
	char *req = malloc(sizeof(char)*(strlen(name)+10));
	char *rel = malloc(sizeof(char)*(strlen(name)+10));
	int reqfd, relfd; 
	char buf[] = "c";
	char relbuf[] = "";
	strcpy(req, name);
	strcpy(rel, name);

	strcat(req, ".request");
	strcat(rel, ".release");
		
	while(1) {
		if ((reqfd = open(req, O_WRONLY)) == -1 && (errno != EEXIST)) {
			perror("Client Failed to open request FIFO");
		}
		if (write(reqfd, buf, 1) == -1) {
			perror("Client Failed to read from request");
			return -1;
		}
		
		if (reqfd > 0)
			close(reqfd);
		
		if ((relfd = open(rel, O_RDWR)) == -1) { 
			perror("Client Failed to open release FIFO");
		}
		if (read(relfd, relbuf, 1) == -1) {
			perror("Client Failed to read synchronization characters");
			return -1;
		}
		if (relfd > 0 && strlen(relbuf) == 1)
			write(STDOUT_FILENO, relbuf, 1);
			close(relfd);
	}

	free(rel);
	free(req);
	return 0;
}
