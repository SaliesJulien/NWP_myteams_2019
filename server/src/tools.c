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

char *parse_args(server_t *server, int wich_args)
{
    char *cmd = NULL;
    int k = 0;
    int i = 0;
    int quotes = 0;

    cmd = malloc(sizeof(char) * strlen(server->command));
    for (; server->command[i]; i++) {
        for (;server->command[i] && server->command[i] == ' '; i++);
        if (server->command[i] == '"') {
            quotes++;
            if (quotes > wich_args) {
                i++;
                for (;server->command[i] && server->command[i] != '"'; i++)
                    cmd[k++] = server->command[i];
                if (server->command[i] != '"') {
                    free(cmd);
                    return ("Bad cmd");
                }
                else {
                    cmd[k] = '\0';
                    return (cmd);
                }
            }
        }
    }
    free(cmd);
    return ("Bad cmd");
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
