/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** login
*/

#include "server.h"

void list_teams(server_t *server, int client, int id)
{
    dprintf(client, "list of all teams that you are in :\n");
    for (int i = 0; server->clients[id].teams[i].team_id != NULL; i++)
        dprintf(client, "Team name -> \"%s\"    Team ID -> \"%s\"\n",
            server->clients[id].teams[i].team_name,
            server->clients[id].teams[i].team_id);
}

void list_channel(server_t *server, int client, int id)
{
    int i = 0;

    for (i = 0; strcmp(server->clients[id].teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    dprintf(client,
        "List of all channels that you are in for the team \"%s\" :\n",
        server->clients[id].teams[i].team_name);
    for (int k = 0; server->clients[id].teams[i].channel[k].channel_id; k++)
        dprintf(client, "Team name -> \"%s\"    Team ID -> \"%s\"\n",
            server->clients[id].teams[i].channel[k].channel_name,
            server->clients[id].teams[i].channel[k].channel_id);
}

void list_thread(server_t *server, int client, int id)
{
    int i = 0;
    int k = 0;
    int j = 0;

    for (i = 0; strcmp(server->clients[id].teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (k = 0; strcmp(server->clients[id].teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]); k++);
    dprintf(client, "List of thread in the channel \"%s\" :\n",
            server->clients[id].teams[i].channel[k].channel_name);
    for (; server->clients[id].teams[i].channel[k].thread[j].thread_id; j++)
        dprintf(client, "Thread title -> \"%s\"    Thread ID -> \"%s\"\n",
            server->clients[id].teams[i].channel[k].thread[j].thread_title,
            server->clients[id].teams[i].channel[k].thread[j].thread_id);
}

void list_replies(server_t *server, int client, int id)
{
    int i = 0;
    int k = 0;
    int j = 0;
    int c = 0;

    for (i = 0; strcmp(server->clients[id].teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (k = 0; strcmp(server->clients[id].teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]); k++);
    for (; strcmp(server->clients[id].teams[i].channel[k].thread[j].thread_id,
        server->clients[id].use_state[2]); j++);
    dprintf(client, "Thread \"%s\" Replies :\n",
            server->clients[id].teams[i].channel[k].thread[j].thread_title);
    for (;server->clients[id].teams[i].channel[k].thread[j].comment[c]; c++)
        dprintf(client, "Reply -> \"%s\"\n",
            server->clients[id].teams[i].channel[k].thread[j].comment[c]);
}

void list(server_t *server, int client, int id)
{
    if (server->clients[id].use_state[2])
        list_replies(server, client, id);
    if (server->clients[id].use_state[1] &&
        !server->clients[id].use_state[2])
        list_thread(server, id, client);
    if (server->clients[id].use_state[0] &&
        !server->clients[id].use_state[1])
        list_channel(server, client, id);
    if (!server->clients[id].use_state[0])
        list_teams(server, client, id);
}