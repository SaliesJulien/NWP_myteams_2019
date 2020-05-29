/*
** EPITECH PROJECT, 2020
** tools.c
** File description:
** tools.c
*/

#include "server.h"

bool uuid_exit(server_t *server, char *uuid_find)
{
    for (int i = 0; i < server->nb_clients; i++)
        if (strcmp(server->clients[i].user_id, uuid_find) == 0)
            return (true);
    return (false);
}

int uuid_index(server_t *server, char *uuid_find)
{
    for (int i = 0; i < server->nb_clients; i++)
        if (strcmp(server->clients[i].user_id, uuid_find) == 0)
            return (i);
    return (-1);
}

char *return_args(server_t *server, int i, char *cmd, char *error_cmd)
{
    int k = 0;

    for (;server->command[i] && server->command[i] != '"'; i++)
        cmd[k++] = server->command[i];
    if (server->command[i] != '"') {
        free(cmd);
        return (error_cmd);
    }
    else {
        cmd[k] = '\0';
        free(error_cmd);
        return (cmd);
    }

}

char *find_arg(server_t *server, int i, char **cmd_array, int *count)
{
    if (server->command[i] == '"') {
        count[0]++;
        if (count[0] > count[1]) {
            return (return_args(server, i + 1, cmd_array[0], cmd_array[1]));
        }
    }
    return (NULL);
}

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

void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();

    while (clock() < start_time + milli_seconds);
}