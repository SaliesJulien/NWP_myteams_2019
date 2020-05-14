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
    dprintf(client, "You are now in the server home.\n");

}

void back_team(server_t *server, int client, int id)
{
    int i = 0;

    for (; strcmp(server->teams[i].team_id, server->clients[id].use_state[0]);
        i++);
    dprintf(client, "You are now in the team \"%s\"\n",
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
    dprintf(client, "You are now in the channel \"%s\"\n",
        server->teams[i].channel[k].channel_name);
    server->clients[id].use_state[2] = NULL;

}

void use_back(server_t *server, int client, int id)
{
    if (server->clients[id].use_state[2])
        back_channel(server, client, id);
    else if (server->clients[id].use_state[1])
        back_team(server, client, id);
    else if (server->clients[id].use_state[0])
        back_server(server, client, id);
    else
        dprintf(client, "551 You can't go deeper.\n");
}