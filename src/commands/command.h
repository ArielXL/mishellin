#include <stdlib.h>
#include <stdio.h>

typedef struct Command {
    struct Command *NextCommand;

    /* Parsed args -- arg[0] */
    char *lex;
    char **args;

    /* Stdin -- Stdout */
    char *input;
    char *output;

    /* Redirected In or Out */
    char *input_file;
    char **output_files;
    char **output_files_app;

    /* Redirected In or Out */
    int has_input;
    int has_output;
    int has_output_app;

    /* FLAGS */
    int empty;
    int first;
    int has_redirect;
    int itsbg;
    int parsed;
    int executed;
} Command_t;

typedef struct CommandList {
    Command_t *Commands;
    int len;
} CommandList_t;
