#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>


#ifndef _LIST_H_

	#define _LIST_H_ 1

	/*
		Cycle array implmentation
	*/
	typedef struct list {
		int len;
		int current_pointer;
		int init_pointer;
		char *base[50];
		char *path;

	} list_t;

	extern void printf_history(list_t *l, int fd, int to_store);
	extern void push_back(list_t *l, char *value);
	extern char *fgets_all(int fd);
	extern char *get_command(list_t *l, int command_num);
	extern void dispose_list(list_t *l);
	extern void init_list(list_t *l, char *path);

#endif