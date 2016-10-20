#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#define MAXNAME 80
#define READ_FLAGS O_RDONLY
#define WRITE_FLAGS (O_WRONLY | O_CREAT | O_TRUNC)

void *copyfilepass(void *arg);

void *copydirectory(void *arg) {
	fprintf(stdout, "Received arg %s\n", (char *)arg);
	char * args = (char *)arg;	
	char *from = strtok(args, "|");	
	char *to = strtok(NULL, "|");
	DIR *fromdir = opendir(from);
	DIR *todir = opendir(to);
 	struct dirent *ent = NULL;
	int fds[2];
	int error;
	char tmp[MAXNAME+MAXNAME];
	pthread_t tid;

	if (fromdir == NULL || todir == NULL) {
		fprintf(stderr, "Failed to open directories %s %s \n", from, to);	
		return 1;	
	}

	fprintf(stdout, "Directory %s opened\n", from);	
	fprintf(stdout, "Directory %s opened\n", to);	
	while((ent = readdir(fromdir)) != NULL) {
		if (ent->d_type == DT_DIR) {
			continue;
		} else {
			memset((void *)tmp, 0, MAXNAME+MAXNAME);
			strcat(tmp, from);	
			strcat(tmp, &ent->d_name[0]);	
			fprintf(stdout, "Attempting to open: %s\n", tmp);	
			if (((fds[0] = open(tmp, READ_FLAGS)) == -1)) {
					perror("Failed to open the file");
					return 1;
			}
			
			memset((void *)tmp, 0, MAXNAME+MAXNAME);
			strcat(tmp, to);	
			strcat(tmp, &ent->d_name[0]);	
			
			fprintf(stdout, "Attempting to copy to: %s\n", tmp);	
			if ((fds[1] = open(
				tmp, O_RDWR | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH)) == -1) {
				perror("Failed to create new file");	
				return 1;
			}

			if (error = pthread_create(&tid, NULL, copyfilepass, fds)) {
				fprintf(stderr, "Failed to create thread: %s\n", strerror(error));
				return 1;
			}
			if (error = pthread_join(tid, (void **)NULL)) {
				fprintf(stderr, "Failed to join thread: %s\n", strerror(error));
				return 1;
			}
		}	
	}
	closedir(fromdir);
	closedir(todir);
	return 0;
}
