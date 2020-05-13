/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** login
*/

#include "server.h"

void list_clients_logged(server_t *server, int client, int id)
{
    (void)id;
    dprintf(client, "List of users logged in on the server\n");
    for (int i = 0; i < server->nb_clients; i++)
        if (server->clients[i].logged)
            dprintf(client, "Username : \"%s\"    User ID : \"%s\"\n",
            server->clients[i].user_name, server->clients[i].user_id);
}

void list_team_info(server_t *server, int client, int id)
{
    int i = 0;

    dprintf(client, "Team infos :\n");
    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    dprintf(client, "Team name : \"%s\"    Team description : \"%s\"\n",
        server->teams[i].team_name,
        server->teams[i].team_desc);
}

void list_channel_info(server_t *server, int client, int id)
{
    int i = 0;
    int k = 0;

    dprintf(client, "Channel infos :\n");
    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (k = 0; strcmp(server->teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]); k++);
    dprintf(client, "Channel name : \"%s\"    Channel description : \"%s\"\n",
        server->teams[i].channel[k].channel_name,
        server->teams[i].channel[k].channel_desc);
}

void list_thread_info(server_t *server, int client, int id)
{
    int i = 0;
    int k = 0;
    int j = 0;

    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (k = 0; strcmp(server->teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]); k++);
    for (; strcmp(server->teams[i].channel[k].thread[j].thread_id,
        server->clients[id].use_state[2]); j++);
    dprintf(client, "Thread title : \"%s\"    Thread description : \"%s\"\n",
        server->teams[i].channel[k].thread[j].thread_title,
        server->teams[i].channel[k].thread[j].thread_content);
}

void info(server_t *server, int client, int id)
{
    if (server->clients[id].use_state[2])
        list_thread_info(server, client, id);
    if (server->clients[id].use_state[1] &&
        !server->clients[id].use_state[2])
        list_channel_info(server, id, client);
    if (server->clients[id].use_state[0] &&
        !server->clients[id].use_state[1])
        list_team_info(server, client, id);
    if (!server->clients[id].use_state[0])
        list_clients_logged(server, client, id);
}