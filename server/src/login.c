/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** login
*/

#include "server.h"

void login_user(server_t *server, int client, int id)
{
    if ((server->clients[id].user_name = parse_first_args(server)) != NULL) {
        server->clients[id].logged = true;
        dprintf(client, "Client logged in.\r\n");
    } else {
        dprintf(client, "Bad arguments\r\n");
    }
}
