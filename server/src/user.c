/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** user
*/

#include "server.h"

bool find_user(server_t *server, char *user_id, int id)
{
    for (int i = 0; i < server->nb_clients; i++) {
        if (strcmp(user_id, server->clients[i].user_id) == 0) {
            dprintf(server->clients[id].fd_client,
                "User name -> %s.\r\n", server->clients[i].user_name);
            return (true);
        }
    }
    return(false);
}

void user(server_t *server, int client, int id)
{
    char *user_id = parse_args(server, 0);

    if (server->clients[id].logged == false) {
        dprintf(client, "Not logged in.\r\n");
    } else if (strcmp(user_id, "Bad cmd") != 0) {
        if ((find_user(server, user_id, id)) == false)
            dprintf(client, "User ID unknown.\r\n");
    } else {
        dprintf(client, "Bad argument.\r\n");
    }
}
