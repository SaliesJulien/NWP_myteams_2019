/*
** EPITECH PROJECT, 2020
** server.c
** File description:
** server.c
*/

#include "server.h"

void save_thread(server_t *server, FILE *thread_teams, int i)
{
    for (int a = 0; a < server->teams[i].nb_channel; a++) {
        if (server->teams[i].channel[a].thread == NULL)
            return;
        fwrite(server->teams[i].channel[a].thread, sizeof(thread_t),
            server->teams[i].channel[a].nb_thread, thread_teams);
    }
}

void save_channel(server_t *server, FILE *channel_teams, int i)
{
    if (server->teams[i].channel == NULL)
        return;
    fwrite(server->teams[i].channel, sizeof(channel_t),
        server->teams[i].nb_channel, channel_teams);
}

void save_teams(server_t *server, FILE *channel_teams, FILE *thread_teams)
{
    if (thread_teams == NULL || channel_teams == NULL)
        return;
    for (int i = 0; i < server->nb_teams; i++) {
        save_channel(server, channel_teams, i);
        save_thread(server, thread_teams, i);
    }
}

void save_members(server_t *server, FILE *members_teams)
{
    for (int i = 0; i < server->nb_teams; i++) {
        if (server->teams[i].members == NULL)
            continue;
        fwrite(server->teams[i].members, sizeof(members_t),
            server->teams[i].nb_members, members_teams);
    }
}

void save_struct(server_t *server)
{
    for (int j = 0; j < server->nb_clients; j++) {
        if (server->clients[j].active == true) {
            dprintf(server->clients[j].fd_client,
                "221 Service closing control connection\r\n");
            server->clients[j].active = false;
        }
    }
}
