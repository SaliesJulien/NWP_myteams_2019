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

char *parse_first_args(server_t *server)
{
    char *uuid_str = calloc(DEFAULT_BODY_LENGTH, sizeof(char));
    int compt = 0;

    for (size_t i = 0; i < strlen(server->command); i++) {
        if (server->command[i] == '"') {
            i++;
            for (size_t j = i; server->command[j] != '"'; j++) {
                uuid_str[compt] = server->command[j];
                compt++;
            }
            break;
        }
    }
    uuid_str[compt] = '\0';
    return (uuid_str);
}