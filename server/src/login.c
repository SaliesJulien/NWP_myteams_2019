/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** login
*/

#include "server.h"

bool check_exist(server_t *server, int client, int id, int i)
{
    if ((strcmp(server->clients[i].user_name,
        server->clients[id].user_name) == 0) && (i != id)) {
        if (server->clients[i].active == false) {
            server->clients[i].active = true;
            server->clients[i].logged = true;
            server->clients[i].fd_client = server->clients[id].fd_client;
            server->clients[id].fd_client = -1;
            server->clients[id].active = false;
            dprintf(client, "Client logged in.\r\n");
            return (true);
        } else {
            dprintf(client, "This client is already logged in.\r\n");
            return (true);
        }
    }
    return (false);
}

void find_uuid(server_t *server, int client, int id)
{
    bool check = false;

    for (int i = 0; i < server->nb_clients; i++) {
        if ((check_exist(server, client, id, i)) == true) {
            check = true;
            break;
        }
    }
    if (check == false) {
        strcpy(server->clients[id].user_id, generate_id());
        dprintf(client, "Client logged in.\r\n");
        server->clients[id].logged = true;
    }
}

void login_user(server_t *server, int client, int id)
{
    if ((strcpy(server->clients[id].user_name, parse_args(server, 0))) != NULL) {
        find_uuid(server, client, id);
    } else {
        dprintf(client, "Bad arguments\r\n");
    }
}
