#include "execution.h"
#include "command.h"

int broken_pipe(CommandList_t cmdlist) {
    for (int j = 0; j < cmdlist.len; ++j)
        if (cmdlist.Commands[j].empty)
            return 1;
    return 0;
}

int builtin_command(Command_t command, list_t *l) {
    if (!strcmp(command.lex, "cd") && (command.args[1] == NULL || (chdir(command.args[1]) == 0)))
        return 1;
    if (!strcmp(command.lex, "exit")){
        dispose_list(l);
        exit(0);
    }
    if (!strcmp(command.lex, "&"))
        return 1;
    if (!strcmp(command.lex, "history")) {
        if(command.args[1] != NULL && !strncmp(command.args[1], "-c", 2))
            clear_history(l);
        else
    	    printf_history(l, 1, 0);
        return 1;
    }
    return 0;
}

int execute_simple(Command_t command, int fdin, list_t *l) {
    int fdout = 1;
    if (!builtin_command(command, l)) {
        int pid = fork();
        if (pid == 0) {
            if (command.has_input) {
                fdin = open(command.input_file, O_RDONLY);
            }
            if (command.has_output_app) {
                for (int i = 0; command.output_files_app[i]; ++i) {
                    if (i > 0) close(fdout);
                    if ((fdout = open(command.output_files_app[i], O_WRONLY | O_APPEND)) < 0) {
                        fdout = open(command.output_files_app[i], O_WRONLY | O_CREAT, 0644);
                    }

                }
            }
            if (command.has_output) {
                for (int i = 0; command.output_files[i]; ++i) {
                    if (fdout >= 0)
                        close(fdout);
                    if ((fdout = open(command.output_files[i], O_WRONLY | O_TRUNC)) < 0) {
                        fdout = open(command.output_files[i], O_WRONLY | O_CREAT, 0644);
                    }
                }
            }
            if (command.has_input) {
                dup2(fdin, 0);
                // close(fdin);
            }
            if (command.has_output || command.has_output_app) {
                dup2(fdout, 1);
                // close(fdout);
            }

            execvp(command.lex, command.args);

            printf("\"%s\" not found \n", command.lex);
            exit(2);
        }
        int status;
        wait(&status);
    }
    return 0;
}

int execute(Command_t command, int fdin, int its_last) {
    int pipefd[2];
    pipe(pipefd);

    int pid = fork();
    if (pid == 0) {
        // child
        close(pipefd[0]);
        int out, fdout;
        fdout = pipefd[1];
        out = fdout;

        if (command.has_input)
            fdin = open(command.input_file, O_RDONLY);

        if (command.has_output_app) {
            for (int i = 0; command.output_files_app[i]; ++i) {
                if (i > 0)
                    close(fdout);
                if ((fdout = open(command.output_files_app[i], O_WRONLY | O_APPEND)) < 0) {
                    fdout = open(command.output_files_app[i], O_WRONLY | O_CREAT, 0644);
                }

            }
        }
        if (command.has_output) {
            for (int i = 0; command.output_files[i]; ++i) {
                if (fdout >= 0)
                    close(fdout);
                if ((fdout = open(command.output_files[i], O_WRONLY | O_TRUNC)) < 0) {
                    fdout = open(command.output_files[i], O_WRONLY | O_CREAT, 0644);
                }
            }
        }

        dup2(fdin, 0);

        if (!its_last || command.has_redirect) {
            dup2(out, 1);
        }

        if (command.itsbg) {
            // bg logic
        } else {
            execvp(command.lex, command.args);
            // error
            printf("\"%s\" not found \n", command.lex);
            exit(0);
        }
    }
    // father
    close(pipefd[1]);

    //bg

    return pipefd[0];
}

int execute_line(CommandList_t cmdlist, list_t *hist) {
    if (broken_pipe(cmdlist))
        return 1;
    if (cmdlist.len == 0)
        return 0;
    int pid = 0, fdin = 0, status = 0;

    if (cmdlist.len == 1) {
        status = execute_simple(cmdlist.Commands[0], fdin, hist);
        return status;
    }
    int i;

    for (i = 0; i < cmdlist.len; ++i)
        fdin = execute(cmdlist.Commands[i], fdin, (i == cmdlist.len - 1));
    while (i-- > 0)
        wait(&status);

    return status;
}
