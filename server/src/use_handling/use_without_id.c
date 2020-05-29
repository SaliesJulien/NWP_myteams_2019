/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

void use_back(server_t *server, int client, int id)
{
    (void)client;
    server->clients[id].use_state[0] = NULL;
    server->clients[id].use_state[1] = NULL;
    server->clients[id].use_state[2] = NULL;
}