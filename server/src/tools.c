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

char *jump_cmd(char *arg, char *tmp, size_t i, int wich_args)
{
    int quotes = 0;

    for (; i < strlen(tmp); i++) {
        quotes += (tmp[i] == '"') ? 1 : 0;
        if (quotes > wich_args) {
            if ((tmp = strchr(tmp + i + 1, '"')) == NULL)
                return (NULL);
            break;
        }
    }
    if (quotes <= wich_args)
        return (NULL);
    arg[strlen(arg) - strlen(tmp)] = 0;
    return (arg + i + 1);
}

char *get_args(char *str, int wich_args)
{
    char *tmp = strdup(str);
    char *arg = NULL;
    size_t i = 0;

    if ((arg = strchr(tmp, ' ')) == NULL)
        return (NULL);
    tmp = strdup(arg);
    for (; i < strlen(tmp) && tmp[i] == ' '; i++);
    if (tmp[i] != '"')
        return (NULL);
    arg = jump_cmd(arg, tmp, i, wich_args);
    if (arg == NULL)
        return (NULL);
    free(tmp);
    return (arg);
}

char *parse_args(server_t *server, int wich_args)
{
    char *uuid_str = get_args(server->command, wich_args);

    return (uuid_str != NULL) ? (uuid_str) : ("Bad cmd");
}

bool count_args(server_t *server, int args_nb)
{
    int i = 0;
    bool name = false;
    int count = 0;

    for (; server->command[i]; i++) {
        if (server->command[i] == ' ') {
            if (!name)
                count++;
            for (;server->command[i] && server->command[i] == ' '; i++);
        }
        if (server->command[i] == '"')
            name = !name;
    }
    return ((count == args_nb) ? true : false);
}
