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

char *get_args(char *str, int wich_args)
{
    char *tmp = strdup(str);
    char *arg = NULL;
    size_t i = 0;
    int quotes = 0;

    if ((arg = strchr(tmp, ' ')) == NULL)
        return (NULL);
    tmp = strdup(arg);
    for (; i < strlen(tmp) && tmp[i] == ' '; i++);
    if (tmp[i] != '"')
        return (NULL);
    for (; i < strlen(tmp); i++) {
        quotes += (tmp[i] == '"') ? 1 : 0;
        if (quotes > wich_args) {
            if ((tmp = strchr(tmp + i + 2, '"')) == NULL)
                return (NULL);
            break;
        }
    }
    arg[strlen(arg) - strlen(tmp)] = 0;
    return (arg + i + 1);
}

char *parse_args(server_t *server, int wich_args)
{
    char *uuid_str = get_args(server->command, wich_args);

    return (uuid_str != NULL) ? (uuid_str) : ("Bad cmd");
}

bool count_args(server_t *server, int args_nb)
{
    int i = 0;
    int count = 0;

    for (; server->command[i]; i++) {
        if (server->command[i] == ' ') {
            count++;
            for (;server->command[i] && server->command[i] == ' '; i++);
        }
    }
    return ((count == args_nb) ? true : false);
}
