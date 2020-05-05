/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** login
*/

#include "server.h"

char *get_sec_arg(char *str)
{
    char *tmp = strdup(str);
    char *arg = NULL;

    if ((arg = strchr(tmp, ' ')) != NULL) {
        arg[strlen(arg) - strlen(rindex(tmp, '\r'))] = 0;
        return (arg + 1);
    }
    return (NULL);
}

void login_user(server_t *server, int client, int id)
{
    if ((server->clients[id].user_name = get_sec_arg(server->command)) != NULL) {
        server->clients[id].logged = true;
        dprintf(client, "Client logged in.\r\n");
    } else {
        dprintf(client, "No arguments\r\n");
    }
}
