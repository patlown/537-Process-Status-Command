//Authors: Patrick Lown, Peter Navin

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "537ps.h"
#include "parser.h"
#include "proc1.h"
#include "output.h"


void get_options(struct flags *flag, int cmdargc, char *cmdargv[]);

//Process command line options
int main(int argc, char *argv[]){

	//call get options and create flag struct
    struct pNode *x;
	struct flags *flag = malloc(sizeof(struct flags));
    get_options(flag,argc, argv);

	if (flag->pFlag == 1){
		//call simple case process list
        x = pidspec(flag->pName);
        //x is a pNode list with only one element.  Can directly pass the pointer to the process using x->data member
        print_process(x->data,flag);
	}
	else {
		//call process list all user processes
        x = pid();
        while(x != NULL){
        	print_process(x->data,flag);
        	x = x->next;
        }
    
	}
    return 0;
} 


void get_options(struct flags *flag, int cmdargc, char *cmdargv[]){
       
    int c;
    extern char *optarg;
    extern int optind;

    char *sName;
    char *uName;
    char *sysTimeName;
    char *vName;
    char *cName;
    char *pName;
    //set up default values for flags before processing
    flag->pName = "";
    flag->pFlag = 0;
    flag->sFlag = 0;
    flag->uFlag = 1;
    flag->sysTimeFlag = 0;
    flag->vFlag = 0;
    flag->cFlag = 1;    

    //process cmdline args using getopt()
    while ((c = getopt (cmdargc, cmdargv, "p:s::U::S::v::c::")) != -1){
        switch (c) {
            case 'p':
                pName = optarg;
                flag->pName = pName;
                flag->pFlag = 1;
                break;
            
            case 's':
                sName = optarg;
                if(sName == NULL){
                    flag->sFlag = 1;
                }
                else if(strcmp(sName,"-") == 0){
                    flag->sFlag = 0;
                }
                break;
            
            case 'U':
                uName = optarg;
                if(uName == NULL){
                    flag->uFlag = 1;
                }
                else if(strcmp(uName, "-") == 0){
                    flag->uFlag = 0;
                }
                break;

            case 'S':
                sysTimeName = optarg;
                if(sysTimeName == NULL){
                    flag->sysTimeFlag = 1;
                }
                else if(strcmp(sysTimeName, "-") == 0){
                    flag->sysTimeFlag = 0;
                }
                break;
                        
            case 'v':
                vName = optarg;
                if (vName == NULL){
                    flag->vFlag = 1;
                }
                else if(strcmp(vName, "-") == 0){
                    flag->vFlag = 0;
                }
                break;
                            
            case 'c':
                cName = optarg;
                if (cName == NULL){
                     flag->cFlag = 1;
                }
                else if(strcmp(cName, "-") == 0){
                    flag->cFlag = 0;
                }
                break;
            }
    }
}
