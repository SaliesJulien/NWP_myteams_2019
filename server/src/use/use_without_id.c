/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

void use_back(server_t *server, int client, int id)
{
    if (server->clients[id].use_state[0])
        free(server->clients[id].use_state[0]);
    if (server->clients[id].use_state[1])
        free(server->clients[id].use_state[1]);
    if (server->clients[id].use_state[2])
        free(server->clients[id].use_state[2]);
    server->clients[id].use_state[0] = NULL;
    server->clients[id].use_state[1] = NULL;
    server->clients[id].use_state[2] = NULL;
    dprintf(client, "213 You are now in the server home\n");
}