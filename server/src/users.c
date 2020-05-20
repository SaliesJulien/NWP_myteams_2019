/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** users
*/

#include "server.h"

void get_list(server_t *server, int client)
{
    dprintf(client, "202 List of all users existing on the server\r\n");
    for (int i = 0; i < server->nb_clients; i++) {
        if ((strcmp(server->clients[i].user_id, "Deleted") != 0) &&
            (strcmp(server->clients[i].user_id, "") != 0)) {
            dprintf(client, "Username : %s    ID : %s\r\n",
                server->clients[i].user_name,
                server->clients[i].user_id);
            dprintf(client, "108|%s|%s|10:20|%d|\n",
                server->clients[i].user_id,
                server->clients[i].user_name,
                server->clients[i].logged == true ? 1 : 0);
        }
    }
}

void users_list(server_t *server, int client, int id)
{
    if (strcmp(server->command, "/users\r\n") == 0)
        (server->clients[id].logged == true) ?
            get_list(server, client) : dprintf(client,
                "515 User not logged\r\n");
    else
        dprintf(client, "501 Error syntax in parameters or arguments\r\n");
}
