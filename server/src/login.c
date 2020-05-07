/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** login
*/

#include "server.h"

void login_user(server_t *server, int client, int id)
{
    if ((strcpy(server->clients[id].user_name, parse_args(server, 0))) != NULL) {
        server->clients[id].logged = true;
        dprintf(client, "Client logged in.\r\n");
    } else {
        dprintf(client, "Bad arguments\r\n");
    }
}
