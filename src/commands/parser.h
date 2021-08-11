#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../utilities/list.h"

#ifndef _PARSER_H

	#define _PARSER_H 1
	extern void push_back(list_t *l, char *value);
	extern char *get_command(list_t *l, int command_num);

	#define MAXARGS 128
	#define MAXLINE 300

#endif