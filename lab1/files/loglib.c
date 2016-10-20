#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "log.h"
 
typedef struct list_struct {
     data_t item;
     struct list_struct *next;
} log_t;
 
static log_t *headptr = NULL;
static log_t *tailptr = NULL;
 
int addmsg(data_t data) {
  log_t *newnode;
	int nodesize;
		 
	nodesize = sizeof(log_t) + strlen(data.string) + 1;

	if ((newnode = (log_t *)(malloc(nodesize))) == NULL) return -1;
	
	newnode->item.time = data.time;
	newnode->item.string = (char *)newnode + sizeof(log_t);
	strcpy(newnode->item.string, data.string);
	newnode->next = NULL;
	if (headptr == NULL) {
		headptr = newnode;
		tailptr = headptr->next;
	} else if (tailptr == NULL) {
		tailptr = newnode;
	} else {
		tailptr = tailptr->next;
		tailptr = newnode;
	}
	return 0;
}

void clearlog(void) {  
	log_t *tmp;
	while (headptr != NULL) {
		tmp = headptr->next;
		headptr = NULL;
		headptr = tmp;	
	}
	tailptr = NULL;
} 

char *getlog(void) {
	char *str = NULL;
	log_t *tmp = headptr;
	int strsize;
	
	strsize = sizeof(char *) + 1;
	while (tmp->next != NULL) {
		strsize += strlen(tmp->item.string);
		tmp = tmp->next;
	}
	
	if((str = (char *)(malloc(strsize))) == NULL) return NULL;

	tmp = headptr;
	while (tmp->next != NULL) {
		strcat(str, tmp->item.string);
		tmp = tmp->next;
	}
	return str;		
}
 
int savelog(char *filename) {
   FILE *fp; 
   int i;
	 log_t *tmp = headptr;
   if ((fp = fopen(filename, "w")) == NULL) {
      fprintf(stderr, "Failed to open %s", filename);
      return 1;
   }

   while (tmp != NULL) {
      fprintf(fp, "%ld:%s\n", tmp->time, tmp->item.string);
			tmp = tmp->next;
	 }

   return 0;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Usage: %s [log]\n", argv[0]);
		return 1;
	}
	printf("Use 'exit' to exit\n");
	while (1) {
		data_t newitem;
		char newmsg[256];
		printf("Enter new message: ");
		fgets(newmsg, 255, stdin);	

		if (strcmp(newmsg, "exit") == 0) break;	

		newitem.time = time(NULL);
		newitem.string = newmsg;

		addmsg(newitem);
	
		savelog(argv[1]);
	}
	return 0;
}
