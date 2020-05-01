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
}
