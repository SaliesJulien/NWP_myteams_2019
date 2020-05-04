/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** users
*/

#include "server.h"

void get_list(server_t *server, int client)
{
    dprintf(client, "List of all users that exist on the domain :\r\n");
    for (int i = 0; i < server->nb_clients; i++)
        dprintf(client, "ID -> %s\r\n", server->clients[i].user_id);
}

void users_list(server_t *server, int client, int id)
{
    if (strcmp(server->command, "/users\r\n") == 0)
        (server->clients[id].logged == true) ?
            get_list(server, client) : dprintf(client, "Not logged in.\r\n");
    else
        dprintf(client, "Bad argument\r\n");
}
