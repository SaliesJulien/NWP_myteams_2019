/*
** EPITECH PROJECT, 2020
** send.c
** File description:
** send.c
*/

#include "server.h"

void send_messages(server_t *server, int client, int id)
{
    (void)id;
    dprintf(client, "Messages %s.\r\n", server->command);
}