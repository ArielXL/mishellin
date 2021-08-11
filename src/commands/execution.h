#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/wait.h>

#ifndef _EVALUATOR_H
	#define _EVAUATOR_H 1
	#define MAXARGS 128
	#define MAXLINE 300

	#include "../utilities/list.h"

#endif

extern int cd(char *path);
extern void clear_history(list_t *l);
extern void dispose_list(list_t *l);
