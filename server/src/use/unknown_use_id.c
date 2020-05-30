/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

void unknown_thread(clients_t *clients, char *thread)
{
    dprintf(clients->fd_client, "306 Thread doesn't exist\r\n");
    delay(1);
    dprintf(clients->fd_client, "116|%s|\r\n", thread);
    free(thread);
}

void unknown_channel(clients_t *clients, char *chan)
{
    dprintf(clients->fd_client, "305 Channel doesn't exist\r\n");
    delay(1);
    dprintf(clients->fd_client, "115|%s|\r\n", chan);
    free(chan);
}

void unknown_team(server_t *server, char *team, int id)
{
    dprintf(server->clients[id].fd_client, "304 Team doesn't exist\r\n");
    delay(1);
    dprintf(server->clients[id].fd_client, "114|%s|\r\n", team);
    free(team);
}