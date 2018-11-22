#include "evaluator.h"

void free_command(Command_t command) {
    if (command.empty)
        return;
    // free(command.input);
    // free(command.output);    --> NOT SURE
    // free(command.NextCommand);
    if (command.has_input)
        free(command.input_file);
        //free -> input file name

    if (command.has_output) {
        //free -> output file names
        for(int i = 0; i < command.has_output; ++i) {
            free(command.output_files[i]);
        }
        free(command.output_files);
    }

    if (command.has_output_app) {
        //free -> output file append names
        for(int i = 0; i < command.has_output_app; ++i) {
            free(command.output_files_app[i]);
        }
        free(command.output_files_app);
    }
    //free -> args
    for(int i = 0; command.args[i] ; ++i) {
        free(command.args[i]);
    }
    //free -> command lex
    free(command.lex);
    free(command.args);

}

void free_command_list(CommandList_t cmdlist) {
    for(int i=0; i < cmdlist.len; ++i) {
        free_command(cmdlist.Commands[i]);
    }
    free(cmdlist.Commands);
}


/* eval - Evaluate a command line */
void eval(char *cmdline, list_t *hist) {
    char buf[MAXLINE];// = malloc(sizeof(char) * (strlen(cmdline) + 1));
    /* Holds modified command line */

    CommandList_t cmd_list;
    strcpy(buf, cmdline);

    cmd_list = parse(buf, hist);

    int errors = execute_line(cmd_list, hist);

    // free_command_list(cmd_list);

}
