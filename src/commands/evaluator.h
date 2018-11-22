#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "command.h"
#include "../utilities/list.h"

#ifndef _EVALUATOR_H
	#define _EVAUATOR_H 1
	#define MAXARGS 128
	#define MAXLINE 300

	extern int execute_line(CommandList_t *cmdlist, list_t *l);
	extern int cd(char *path);
	extern CommandList_t parse(char *cmd_line, list_t *l);

#endif