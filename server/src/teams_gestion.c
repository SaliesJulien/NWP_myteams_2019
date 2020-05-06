/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

void create(server_t *server, int client, int id)
{
    (void)client;
    (void)id;
    if (server->clients[id].use_state == UNDEFINED)
        dprintf(client, "OEOEOE\n");
}

void use(server_t *server, int client, int id)
{
    (void)server;
    (void)client;
    (void)id;
}