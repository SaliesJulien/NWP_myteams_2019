/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** login
*/

#include "server.h"

void list_teams(server_t *server, int client)
{
    int i = 0;

    dprintf(client, "231 List of teams that exist on the server\n");
    for (i = 0; strcmp(server->teams[i].team_id, "NULL"); i++)
        dprintf(client, "Team name -> \"%s\"    Team ID -> \"%s\"\n",
            server->teams[i].team_name,
            server->teams[i].team_id);
    (i == 0) ? dprintf(client, "There is no any team.\n") : (0);
}

void list_channel(server_t *server, int client, int id)
{
    int i = 0;
    int k = 0;

    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    dprintf(client, " 232 List of channels that exist on this team\n",
        server->teams[i].team_name);
    for (k = 0; strcmp(server->teams[i].channel[k].channel_id, "NULL"); k++)
        dprintf(client, "Channel name -> \"%s\"    Channel ID -> \"%s\"\n",
            server->teams[i].channel[k].channel_name,
            server->teams[i].channel[k].channel_id);
    (k == 0) ? dprintf(client, "There is no channel in this team.\n") : (0);
}

void list_thread(server_t *server, int client, int id)
{
    int i = 0;
    int k = 0;
    int j = 0;

    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (k = 0; strcmp(server->teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]); k++);
    dprintf(client, "233 List of threads that exist on this channel\n",
            server->teams[i].channel[k].channel_name);
    for (; strcmp(server->teams[i].channel[k].thread[j].thread_id, "NULL");
        j++)
        dprintf(client, "Thread title -> \"%s\"    Thread ID -> \"%s\"\n",
            server->teams[i].channel[k].thread[j].thread_title,
            server->teams[i].channel[k].thread[j].thread_id);
    (j == 0) ? dprintf(client, "There is no thread in this channel.\n") : (0);
}

void list_replies(server_t *server, int client, int id)
{
    int i = 0;
    int k = 0;
    int j = 0;
    int c = 0;

    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (k = 0; strcmp(server->teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]); k++);
    for (; strcmp(server->teams[i].channel[k].thread[j].thread_id,
        server->clients[id].use_state[2]); j++);
    dprintf(client, "234 List of comment that are posted on this thread\n",
            server->teams[i].channel[k].thread[j].thread_title);
    for (; strcmp(server->teams[i].channel[k].thread[j].comment[c], "NULL")
        ; c++)
        dprintf(client, "Reply -> \"%s\"\n",
            server->teams[i].channel[k].thread[j].comment[c]);
    (c == 0) ? dprintf(client, "There is no comment in this thread.\n") : (0);
}

void list(server_t *server, int client, int id)
{
    if (server->clients[id].use_state[2])
        list_replies(server, client, id);
    if (server->clients[id].use_state[1] &&
        !server->clients[id].use_state[2])
        list_thread(server, client, id);
    if (server->clients[id].use_state[0] &&
        !server->clients[id].use_state[1])
        list_channel(server, client, id);
    if (!server->clients[id].use_state[0])
        list_teams(server, client);
}