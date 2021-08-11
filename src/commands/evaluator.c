#include "evaluator.h"

void free_command(Command_t *command) {
/*
 * --> 'NOT SURE'
 */
    if (command->empty)
        return;
    // free(command.input);
    // free(command.output);
    // free(command.NextCommand);
    if (command->has_input){
        command->has_input = 0;
        // free(command->input_file);
        //free -> input file name
    }

    if (command->has_output) {
        //free -> output file names
        for(int i = 0; i < command->has_output; ++i) {
            free(command->output_files[i]);
        }
        command->has_output = 0;
        // free(command->output_files);
    }

    if (command->has_output_app) {
        //free -> output file append names
        for(int i = 0; i < command->has_output_app; ++i) {
            free(command->output_files_app[i]);
        }
        command->has_output_app = 0;
        // free(command->output_files_app);
    }
    //free -> args
    for(int i = 0; command->args[i] ; ++i) {
        free(command->args[i]);
    }
    //free -> command lex
    // free(command->lex);
    // free(command->args);
}

void free_command_list(CommandList_t *cmdlist) {
    for(int i=0; i < cmdlist->len; ++i) {
        free_command(&cmdlist->Commands[i]);
    }
    cmdlist->len = 0;
    // free(cmdlist->Commands);
}



/* eval - Evaluate a command line */
void eval(char *cmdline, list_t *hist) {
    char *buf = malloc(sizeof(char) * (strlen(cmdline)));
    /* Holds modified command line */

    CommandList_t cmd_list;
    strcpy(buf, cmdline);

    cmd_list = parse(buf, hist);

    execute_line(&cmd_list, hist);

    free(buf);

    free_command_list(&cmd_list);

}
