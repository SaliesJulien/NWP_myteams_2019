/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

void back_server(server_t *server, int client, int id)
{
    server->clients[id].use_state[0] = NULL;
    dprintf(client, "213 You are now in the server\r\n");

}

void back_team(server_t *server, int client, int id)
{
    int i = 0;

    for (; strcmp(server->teams[i].team_id, server->clients[id].use_state[0]);
        i++);
    dprintf(client, "210 You are now in the team \"%s\"\r\n",
        server->teams[i].team_name);
    server->clients[id].use_state[1] = NULL;

}

void back_channel(server_t *server, int client, int id)
{
    int i = 0;
    int k = 0;

    for (; strcmp(server->teams[i].team_id, server->clients[id].use_state[0]);
        i++);
    for (; strcmp(server->teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]);
        k++);
    dprintf(client, "211 You are now in the channel \"%s\"\r\n",
        server->teams[i].channel[k].channel_name);
    server->clients[id].use_state[2] = NULL;

}

void use_back(server_t *server, int client, int id)
{
    (void)client;
    server->clients[id].use_state[0] = NULL;
    server->clients[id].use_state[1] = NULL;
    server->clients[id].use_state[2] = NULL;
}