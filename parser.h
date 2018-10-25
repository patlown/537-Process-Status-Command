//Authors: Patrick Lown, Peter Navin

#ifndef PARSER_H_   /* Include guard */
#define PARSER_H_

  /* An example function declaration */

struct process {
	char * pid;
	char status;
	unsigned long int utime;
	unsigned long stime;
	int size;
	size_t length;
	char arg_list[1024];
};


struct pNode 
{
	struct process *data;
	struct pNode *next;
};

void process_parser(struct process *pc,char *Pid);

#endif // PARSER_H_
