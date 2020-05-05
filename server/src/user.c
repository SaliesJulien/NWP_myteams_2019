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
        if (strcmp(user_id, server->clients[id].user_id) == 0) {
            dprintf(server->clients[id].fd_client,
                "User name -> %s.\r\n", server->clients[id].user_name);
            return (true);
        }
    }
    return(false);
}

void user(server_t *server, int client, int id)
{
    char *user_id = calloc(DEFAULT_BODY_LENGTH, sizeof(char));

    if (server->clients[id].logged == false) {
        dprintf(client, "Not logged in.\r\n");
    } else if ((user_id = parse_first_args(server)) != NULL) {
        if ((find_user(server, user_id, id)) == false)
            dprintf(client, "User ID unknown.\r\n");
    } else {
        dprintf(client, "Bad argument.\r\n");
    }
}
