/*
** EPITECH PROJECT, 2020
** generate random ID
** File description:
** myteams
*/

#include "server.h"

void init_team_and_conv(server_t *server)
{
    server->clients[server->nb_clients].teams = malloc(sizeof(team_t));
    server->clients[server->nb_clients].teams[0].team_name = NULL;
    server->clients[server->nb_clients].teams[0].team_desc = NULL;
    server->clients[server->nb_clients].teams[0].team_id = NULL;
    server->clients[server->nb_clients].conversation =
        malloc(sizeof(messages_t));
    server->clients[server->nb_clients].conversation[0].client_id = NULL;
    server->clients[server->nb_clients].conversation[0].message = NULL;
}

void new_client_struct(server_t *server, int fd)
{
    server->clients = realloc(server->clients,
        sizeof(clients_t) * (server->nb_clients + 2));
    server->clients[server->nb_clients].fd_client = fd;
    server->clients[server->nb_clients].logged = false;
    strcpy(server->clients[server->nb_clients].user_name, "");
    server->clients[server->nb_clients].active = true;
    server->clients[server->nb_clients].use_state = malloc(sizeof(char *) * 3);
    server->clients[server->nb_clients].use_state[0] = NULL;
    server->clients[server->nb_clients].use_state[1] = NULL;
    server->clients[server->nb_clients].use_state[2] = NULL;
    init_team_and_conv(server);
}
