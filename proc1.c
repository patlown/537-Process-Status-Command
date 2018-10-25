//Authors: Patrick Lown, Peter Navin

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h> 
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "parser.h"


//function that creates a file path for ex: "/proc/1234" if give v was '1234'
char* fpath(char *v){
	char *proc = "/proc/";
	char* cat = (char *) malloc(1+strlen(proc) + strlen(v));
	strcpy(cat,proc);
	strcat(cat,v);
    return cat;
}

char* fpathpid(char *v,char *x){
	char *proc = "/proc/";
	char* cat = (char *) malloc(1+strlen(proc) + strlen(v) + strlen(x));
	strcpy(cat,proc);
	strcat(cat,v);
	strcat(cat,x);
    return cat;
}

int isprocess(char *path){
    char uid[255], u[255], buff[255] = "";
    FILE *fp;
    fp = fopen(path, "rt");
    int status;
    
    for(int i = 0; i < 9; i++){
        strcpy(uid, fgets(buff, 255, fp));
    }

    sprintf(u, "%d", geteuid());

    if(strstr(uid, u) != NULL){
        status =  0;
    }
    else{
        status = 1;
    }
    return status;
 }

int isNumber(char *check){
	int length;
	if(check != NULL){
	length = strlen(check);
	}
	for(int i = 0; i < length; ++i){
		if(isdigit(check[i]) == 0){
		return 1;
		}
	}
	return 0;
}

//this function is called if -p flag is present.  It checks if the pid file exists and parses it and adds it to a list
//if it does.  The 1 element lsit is then returned.
struct pNode* pidspec(char *v){
	
	struct pNode* head = NULL;

	DIR *myDirectory;
	char * pid_path = fpath(v);
	myDirectory = opendir(pid_path);
	if(myDirectory){
		//parse info from directory files
		head  = (struct pNode*)malloc(sizeof(struct pNode));
		head->data = (struct process*)malloc(sizeof(struct process));
		process_parser(head->data, v);
	}else{
		perror("Process does not exist");
		exit(0);
	}
	return head;
}

//This function is called if no -p flag is present in ps call.  It loops through files in proc checking if they are pids and if user owns them
//if so, this will call the parser to get a process struct and add to a process list which is a linked list.  After looping through all processes
//this function will return the head of the list.
struct pNode* pid(){
	struct pNode* head = NULL;
	struct pNode* curr= NULL;

	DIR *myDirectory;
    struct dirent *myFile;
    char* proc = "/proc";
    myDirectory = opendir(proc);
    if (myDirectory) {
   		while ((myFile = readdir(myDirectory))){
			if(isNumber(myFile->d_name) == 0)
			{
				char * pid = myFile -> d_name;
				char* statuspath = fpathpid(pid,"/status");
				
				 if(isprocess(statuspath) == 0)
				{
					if(head == NULL){
						head  = (struct pNode*)malloc(sizeof(struct pNode));
						head->data =  malloc(sizeof(struct process));
						process_parser(head->data, pid);
						curr = head;
					}else{
						curr->next =(struct pNode*)malloc(sizeof(struct pNode));
						curr = curr->next;
						curr-> data = malloc(sizeof(struct process));
						process_parser(curr->data,pid);
					}
				}	

			}
		}

	}
	return head;	
}
