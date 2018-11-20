#include "evaluator.h"

/* eval - Evaluate a command line */
void eval(char *cmdline, list_t *hist) {
    char *buf = malloc(sizeof(char) * (strlen(cmdline) + 1));
    /* Holds modified command line */

    CommandList_t cmd_list;
    strcpy(buf, cmdline);

    cmd_list = parse(buf, hist);

    int errors = execute_line(cmd_list, hist);

}
