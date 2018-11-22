#include "entry.h"
#include "commands/command.h"


int PID_OF_SHELL;

void handler_INT(int sig) {
    if (PID_OF_SHELL != getpid()) {
        exit(0);
    }
}

void init() {
    PID_OF_SHELL = getpid();
    signal(SIGINT, handler_INT);
}

list_t get_init_hist(char *wd, list_t l) {
    wd = getcwd(wd, MAXLINE);

    char *pth_end, *pth_hist;
    pth_hist = malloc(sizeof(char) * (strlen(wd) + 14));
    strcpy(pth_hist, wd);

    pth_end = pth_hist + strlen(wd);

    strcpy(pth_end, "/history.hst");
    init_list(&l, pth_hist);
    return l;
}

void prompt(char *user, char *hosts, char *workd) {
    getcwd(workd, MAXLINE);
    workd = path_fixformat(workd);
    printf("┌─["
    COLOR_CLEAR
    COLOR_GREEN
    COLOR_NEG
    "%s"
    COLOR_CLEAR
    "]["
    COLOR_CLEAR
    COLOR_GREEN
    "%s"
    COLOR_CLEAR
    "] "
    COLOR_RED
    "✗"
    COLOR_CLEAR
    " ["
    COLOR_CLEAR
    COLOR_BLUE
    "%s"
    COLOR_CLEAR
    "]\n"
    COLOR_CLEAR, user, hosts, workd);
    printf("└─▪"
    COLOR_CLEAR
    "$ ");
}

int empty_line(char *line) {
    if (*line == '\0' || *line == '\n')
        return 1;
    return 0;
}

int main(int argc, char const *argv[]) {
    init();
    char *command_line, *my_wd, *my_log, *my_hn;

    my_hn = malloc(sizeof(char) * (MAXLINE / 3));
    my_wd = malloc(sizeof(char) * (MAXLINE / 2));
    my_log = malloc(sizeof(char) * (MAXLINE / 3));

    command_line = malloc(sizeof(char) * MAXLINE);

    gethostname(my_hn, (MAXLINE / 3));
    my_log = getlogin();

    list_t hist;
    hist = get_init_hist(my_wd, hist);

    system("clear");

    while (1) {
        prompt(my_log, my_hn, my_wd);

        fgets(command_line, MAXLINE, stdin);

        if (!empty_line(command_line))
            eval(command_line, &hist);
    }
    return 0;
}
