//Authors: Patrick Lown, Peter Navin


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "537ps.h"
#include "parser.h"
#include "proc1.h"


//creates and returns process struct with info
void process_parser(struct process *proc,char *Pid){
    
    char *pid = Pid;
    char *path = fpathpid(pid,"/stat");
    char *cmdpath = fpathpid(pid,"/cmdline");
    char *statmpath = fpathpid(pid,"/statm");

    int count = 1;
    char buff[255] = "";
    char *delim = " ";
    char *p = buff;
    FILE *fp;
    fp = fopen(path, "rt");
    char *sTime;
    char *uTime;
    char *size;
    char *status;
    if(!fp){
        printf("1) error: file open failed");
    }
    if(!fgets(buff, 255, fp)){
        printf("1)error: read file failed");
    }
    //Tokenizes string and iterates through the tokens, setting vars (/proc/*pid*/stat)
    p = strtok(buff, delim);
    while (p) {
        if(count == 3){
            status = p;
        }
        if(count == 14){
            uTime = p;
        }
        if(count == 15){
            sTime = p;
        }
        p = strtok(NULL, delim);
        count++;
    }
    count = 1;
    fclose(fp);
    char newbuff[255] = "";
    FILE *newfp;
    newfp = fopen(statmpath, "rt");
    p = newbuff;
    
    if(!newfp){
        printf("2) error: file open failed");
    }
    if(!fgets(newbuff, 255, newfp)){
        printf("2)error: read file failed");   
    }
   
    //Tokenizes and sets vars (/proc/*pid*/statm)
    p = strtok(newbuff, delim); 
    while (p){
        if(count == 1){
            size = p;
        }
        p = strtok(NULL, delim);
        count++;
    }
    count = 1;
    fclose(newfp);

    int cmd = open(cmdpath, O_RDONLY);


    char arg_list[1024];
    
    proc -> length = read(cmd, arg_list, sizeof (arg_list));
    arg_list[proc -> length] = '\0';
    close(cmd);


    memcpy(proc->arg_list,arg_list,proc->length);


    //sets process vars
    proc -> pid = pid;
    proc -> status = *status;
    proc-> size = atoi(size);
    proc -> utime = strtol(uTime, NULL, 10); 
    proc -> stime = strtol(sTime, NULL, 10);


	return;
}
