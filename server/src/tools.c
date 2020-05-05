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
        if (strcmp(server->clients->user_id, uuid_find) == 0)
            return (i);
    return (-1);
}

char *get_sec(char *str)
{
    char *tmp = strdup(str);
    char *arg = NULL;

    if ((arg = strchr(tmp, ' ')) == NULL)
        return (NULL);
    tmp = strdup(arg);
    if (tmp[1] != '"')
        return (NULL);
    if ((tmp = strchr(tmp + 2, '"')) == NULL)
        return (NULL);
    arg[strlen(arg) - strlen(tmp)] = 0;
    return (arg + 2);
}

char *parse_first_args(server_t *server)
{
    bool check = false;
    char *uuid_str = calloc(DEFAULT_BODY_LENGTH, sizeof(char));

    if ((uuid_str = get_sec(server->command)) != NULL)
        check = true;
    return (check = true) ? (uuid_str) : (NULL);
}
