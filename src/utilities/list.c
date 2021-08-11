#include "list.h"


void clear_history(list_t *l) {
    int fd = open(l->path, O_CREAT | O_TRUNC, 0664);
    if(fd > 0)
        close(fd);
    init_list(l, l->path);
}

void printf_history(list_t *l, int fd, int to_store) {
    int counter = 0;
    for (int i = l->init_pointer; counter < l->len; ++counter, ++i) {
        i = i == 50 ? 0 : i;
        if (to_store)
            dprintf(fd, "%s\n", l->base[i]);
        else
            dprintf(fd, "%d   %s \n", counter, l->base[i]);
    }
}

void push_back(list_t *l, char *value) {
    value[strlen(value) - 1] = value[strlen(value) - 1] == '\n' ? '\0' : value[strlen(value) - 1];
    int first_time = l->base[l->current_pointer] == NULL;
    l->base[l->current_pointer] = malloc(sizeof(char) * (strlen(value) + 1));
    strcpy(l->base[l->current_pointer], value);
    l->base[l->current_pointer][strlen(value)] = '\0';

    l->current_pointer++;


    l->len = l->len == 50 ? 50 : l->len + 1;

    if (l->current_pointer == l->init_pointer + 1 && !first_time) {
        l->init_pointer++;
        l->init_pointer %= 50;
    }
    l->current_pointer %= 50;
}

char *fgets_all(int fd) {
    char *str;
    char buf = '\0';
    int i = 0, count = 3;
    str = malloc(sizeof(char) * count);
    while (read(fd, &buf, 1)) {
        if (i > count) {
            count = count << 1;
            str = realloc(str, sizeof(char) * count);
        }
        str[i++] = buf;
    }
    str[++i] = '\0';
    return str;
}

char *get_command(list_t *l, int command_num) {
    char *result;

    if (command_num < 0)
        return "cd\n";

    int count = l->len - 1;

    int index;
    for (index = l->init_pointer; command_num && count; --count, --command_num) {
        index++;
        index = index == 50 ? 0 : index;
    }

    result = malloc(sizeof(char *) * strlen(l->base[index]));
    strcpy(result, l->base[index]);

    return result;
}

void dispose_list(list_t *l) {
    int fd = open(l->path, O_WRONLY | O_TRUNC | O_CREAT, 0);
    printf_history(l, fd, 1);
    close(fd);
}

void init_list(list_t *l, char *path) {
    l->len = 0;
    l->path = malloc(sizeof(char) * strlen(path));
    strcpy(l->path, path);
    l->base[0] = NULL;
    l->init_pointer = 0;
    l->current_pointer = 0;

    int fd = open(l->path, O_RDONLY, 0);
    if (fd < 0) {
        fd = open(l->path, O_CREAT, 0664);
        close(fd);
        return;
    }
    char *line;
    char *lines;

    lines = fgets_all(fd);
    line = strtok(lines, "\n");

    while (line) {
        push_back(l, line);
        line = strtok(NULL, "\n");
    }
    close(fd);
}
