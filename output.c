//Authors: Patrick Lown, Peter Navin

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "537ps.h"
#include "parser.h"
#include "proc1.h"


//given a process and flag struct, this function prints output to the console
void print_process(struct process *proc, struct flags *flag)
{
	printf("%s: ",proc->pid);
	if(flag->sFlag == 1){
		printf("%c ",proc->status );
	}
	if(flag->uFlag == 1){
		printf("utime=%lu ",proc->utime );
	}

	if(flag->sysTimeFlag == 1){
			printf("stime=%lu ",proc->stime );
	}
	
	if(flag->vFlag == 1){
			printf("size=%d ",proc->size);
	}
	if(flag->cFlag == 1){
			int first = 0;
			char* next_arg = proc->arg_list;
			while(next_arg < proc ->arg_list + proc ->length){
				if (first == 0){
					printf("[%s", next_arg);
					first = 1;
				}else{
					printf(" %s", next_arg);
				}
				

				next_arg += strlen (next_arg) + 1;
			}
			printf("]");
	}
	printf("\n");
}
