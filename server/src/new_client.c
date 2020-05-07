/*
** EPITECH PROJECT, 2020
** generate random ID
** File description:
** myteams
*/

#include "server.h"

void new_client_struct(server_t *server, int fd)
{
    server->clients = realloc(server->clients,
        sizeof(clients_t) * (server->nb_clients + 2));
    server->clients[server->nb_clients].fd_client = fd;
    server->clients[server->nb_clients].user_id = generate_id();
    server->clients[server->nb_clients].logged = false;
    server->clients[server->nb_clients].user_name = "";
    server->clients[server->nb_clients].use_state = UNDEFINED;
    server->clients[server->nb_clients].teams = malloc(sizeof(team_t) * 1);
    server->clients[server->nb_clients].conversation = malloc(sizeof(messages_t));
    server->clients[server->nb_clients].conversation[0].client_id = NULL;
    server->clients[server->nb_clients].conversation[0].message = NULL;
}
