/*
** EPITECH PROJECT, 2020
** args_gesture.c
** File description:
** args_gesture.c
*/

#include "server.h"

char *parse_args(server_t *server, int wich_args)
{
    int *count = malloc(sizeof(int) * 2);
    char **cmd_array = malloc(sizeof(char *) * 2);
    char *temp = NULL;

    cmd_array[0] = malloc(sizeof(char) * strlen(server->command));
    cmd_array[1] = malloc(sizeof(char) * strlen("Bad cmd") + 1);
    count[0] = 0;
    count[1] = wich_args;
    strcpy(cmd_array[1], "Bad cmd");
    for (int i = 0; server->command[i]; i++) {
        for (;server->command[i] && server->command[i] == ' '; i++);
        temp = find_arg(server, i, cmd_array, count);
        if (temp != NULL) {
            free(count);
            free(cmd_array);
            return (temp);
        }
    }
    free(temp);
    free(cmd_array[0]);
    return (cmd_array[1]);
}

int count_quotes(server_t *server, int i, int count, bool name)
{
    if (!name)
        count++;
    for (;server->command[i] && server->command[i] == ' '; i++);
    return (count);
}

bool count_args(server_t *server, int args_nb)
{
    int i = 0;
    bool name = false;
    int count = 0;

    for (; server->command[i]; i++) {
        if (server->command[i] == ' ') {
            count = count_quotes(server, i, count, name);
        }
        if (server->command[i] == '"')
            name = !name;
    }
    for (i = i - 1; server->command[i] == ' '; i--)
        count--;
    return ((count == args_nb) ? true : false);
}

char *format_cmd(char *str)
{
    char *cmd = NULL;
    char *temp = strdup(str);

    if (index(temp, ' ') != NULL) {
        cmd = strtok(temp, " ");
    } else {
        cmd = strdup(temp);
        free(temp);
    }
    return (cmd);
}

void remove_chars(char *str, char c)
{
    int i = 0;

    for (int y = 0; str[y]; y++)
        if (str[y] != c)
            str[i++] = str[y];
    str[i] = 0;
}