#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "utilities/list.h"


#ifndef _ENTRY_H
	extern char *path_fixformat(char *path);
	extern void eval(char *cmdline, list_t *l);

	#define _ENTRY_H 1
	#define MAXARGS 128
	#define MAXLINE 500

	#define COLOR_BLUE          "\x1b[36m"
	#define COLOR_WHITE_BLUE    "\x1b[34m"
	#define COLOR_YELLOW        "\x1b[33m"
	#define COLOR_ROSE          "\x1b[35m"
	#define COLOR_GREEN         "\x1b[32m"
	#define COLOR_RED           "\x1b[31m"
	#define COLOR_CLEAR         "\x1b[0m"
	#define COLOR_NEG           "\x1b[1m"
#endif
