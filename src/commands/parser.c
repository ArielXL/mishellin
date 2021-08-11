#include "command.h"
#include "parser.h"

void initialize_command(Command_t *command, int line_len) {
    command->output_files_app = malloc(sizeof(char *) * 1);
    command->output_files = malloc(sizeof(char *) * 1);
    command->input_file = NULL;
    command->itsbg = 0;
    command->has_redirect = 0;
    command->has_input = 0;
    command->has_output_app = 0;
    command->has_output = 0;
    command->empty = 1;
    command->executed = 0;
    command->parsed = 0;
    command->lex = NULL;
    command->args = malloc(sizeof(char *) * (line_len + 1));
}

Command_t parse_command(char *cmd) {
    Command_t command;
    initialize_command(&command, (int) strlen(cmd));
    int argc = 0;        /* Number of args */
    char *token = NULL, *last_token = NULL;

    int count_output_files_ap = 1;
    int count_output_files = 1;

    last_token = malloc(sizeof(char) * 1);
    last_token[0] = '\0';

    token = strtok(cmd, "\t \n");
    while (token) {
        if (strncmp(last_token, "<", 1) == 0) {
            command.has_input = 1;
            command.input_file = malloc(sizeof(char) * (strlen(token) + 1));
            strcpy(command.input_file, token);
        } else if (strncmp(last_token, ">>", 2) == 0) {
            if (count_output_files_ap < command.has_output_app) {
                count_output_files_ap = count_output_files_ap << 2;
                command.output_files_app = realloc(command.output_files_app, sizeof(char *) * count_output_files_ap);
            }
            int l = strlen(token);
            command.output_files_app[command.has_output_app] = malloc(sizeof(char) * (l+1));
            strcpy(command.output_files_app[command.has_output_app], token);
            command.output_files_app[command.has_output_app][l] = '\0';
            command.has_output_app++;
        } else if (strncmp(last_token, ">", 1) == 0) {
            if (count_output_files <= command.has_output) {
                count_output_files = count_output_files << 2;
                command.output_files = realloc(command.output_files, sizeof(char *) * count_output_files);
            }

            command.output_files[command.has_output] = malloc(sizeof(char) * (strlen(token) + 1));
            strcpy(command.output_files[command.has_output], token);
            command.has_output++;
        }


        if (strcmp(token, "&") == 0) {
            command.itsbg = 1;
        } else if (*last_token != '<' && *last_token != '>' && *token != '<' && *token != '>') {
            command.empty = 0;
            command.args[argc] = malloc(sizeof(char) * strlen(token));
            strcpy(command.args[argc], token);
            argc++;
        }
        if (*last_token == '\0' && *token == '>') {
            command.empty = 0;
            command.args[argc] = malloc(sizeof(char) * strlen("echo"));
            strcpy(command.args[argc], "echo");
            argc++;
            //adding echo
            command.empty = 0;
            command.args[argc] = malloc(sizeof(char) * 2);
            strcpy(command.args[argc], "");
            argc++;
            //adding ""
        }
        last_token = token;
        token = strtok(NULL, "\t \n");
    }
    command.args[argc] = NULL;

    command.has_redirect = (command.has_output_app + command.has_output != 0);
    command.lex = command.args[0];
    command.parsed = 1;

    return command;
}


int parse_line(char *buf, CommandList_t *cmdlist, list_t *l) {
    /* Number of args */
    int cmd_count = 0;

    Command_t *sub_commands;
    sub_commands = malloc(sizeof(Command_t) * (strlen(buf) / 2 + 4));

    char *token;
    char **tokens;
    tokens = malloc(sizeof(char *) * (strlen(buf) / 2 + 4));

    char *token_to_parse;

    token = strtok(buf, "|");
    while (token) {
        token_to_parse = malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(token_to_parse, token);
        tokens[cmd_count++] = token_to_parse;
        token = strtok(NULL, "|");
    }
    for (int i = 0; i < cmd_count; ++i) {
        sub_commands[i] = parse_command(tokens[i]);
    }
    free(tokens);
    free(token);//modified and not tested
    cmdlist->len = cmd_count;
    cmdlist->Commands = sub_commands;

    return cmd_count;
}


char *search_command(list_t *hist, char *buf) {
    int count = hist->len;
    int n = strlen(buf);
    if (hist->len == 0)
        return "cd\n";

    for (int i = hist->current_pointer - 1; i != hist->init_pointer && count; --count, --i) {
        i = i == -1 ? 49 : i;
        if (strncmp(buf, hist->base[i], n) == 0)
            return hist->base[i];
    }

    return strncmp(buf, hist->base[hist->init_pointer], n) == 0 ? hist->base[hist->init_pointer] : "cd\n";
}

char *store_and_give_cmd(list_t *hist, char *buf) {

    int valid = ((*buf > 32 && *buf < 127) && *buf != ' ' && *buf != '\n');

    while (*buf == ' ')
        buf++;

    if (valid && *buf != '!')
        push_back(hist, buf);

    if (*buf == '!') {
        buf++;
        if (*buf == '!') {
            buf--;
            free(buf);
            buf = get_command(hist, 51);
            char *cpy_buf;
            cpy_buf = malloc(sizeof(char) * strlen(buf));
            strcpy(cpy_buf, buf);
            return cpy_buf;
        } else {
            char *buft;

            buft = strtok(buf, "! \n");

            if (buft == NULL) {
                printf("\"null\" its not a number\n");
                return "\n";
            }

            if (*buft < '0' || *buft > '9')
                return search_command(hist,buft);

            char *cmd;
            cmd = get_command(hist, atoi(buft));

            char *cpy_buf;
            cpy_buf = malloc(sizeof(char) * strlen(cmd));
            strcpy(cpy_buf, cmd);

            return cpy_buf;
        }
    }

    return buf;
}

void print_state(CommandList_t *cmdlist) {
    for (int i = 0; i < cmdlist->len; ++i) {
        printf("%s: \n", cmdlist->Commands[i].lex);
        printf(" - input-file: \n            - %s \n", cmdlist->Commands[i].has_input ? cmdlist->Commands[i].input_file : "\r\r");

        printf(" - output-file: %d \n", cmdlist->Commands[i].has_output);
        for (int k = 0; cmdlist->Commands[i].has_output && cmdlist->Commands[i].output_files[k]; ++k) {
            printf("               %d - %s \n", k, cmdlist->Commands[i].output_files[k]);
        }

        printf(" - output-file-app: %d \n", cmdlist->Commands[i].has_output_app);
        for (int k = 0; cmdlist->Commands[i].has_output_app && cmdlist->Commands[i].output_files_app[k]; ++k) {
            printf("               %d - %s \n", k, cmdlist->Commands[i].output_files_app[k]);
        }
        printf(" - parsed: %d \n", cmdlist->Commands[i].parsed);
        // printf(" - bg: %d \n", cmdlist.Commands[i].itsbg);
        printf(" - empty: %d \n", cmdlist->Commands[i].empty);
        for (int j = 0; cmdlist->Commands[i].args[j]; ++j) {
            printf("\t - %d --> %s\n", j, cmdlist->Commands[i].args[j]);
        }
    }
}

CommandList_t parse(char *cmd_line, list_t *hist) {
    CommandList_t cmd_list;
    /* Holds unmodified command line */
    char *buf;
    buf = malloc(sizeof(char) * (strlen(cmd_line) + 2));

    strcpy(buf, cmd_line);

    buf = store_and_give_cmd(hist, buf);

    parse_line(buf, &cmd_list, hist);

    //
    // print_state(&cmd_list);
    //

    return cmd_list;
}