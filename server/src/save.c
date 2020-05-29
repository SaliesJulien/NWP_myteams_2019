/*
** EPITECH PROJECT, 2020
** server.c
** File description:
** server.c
*/

#include "server.h"

void save_server(server_t *server)
{
    FILE *file_server = fopen("server_log", "wb");

    for (int j = 0; j < server->nb_clients; j++) {
        if (server->clients[j].active == true) {
            dprintf(server->clients[j].fd_client,
                "221 Service closing control connection\r\n");
            server->clients[j].active = false;
        }
    }
    if (file_server != NULL)
        fwrite(server, sizeof(server_t), 1, file_server);
    fclose(file_server);
}

void save_client(server_t *server)
{
    FILE *file_client = fopen("client_log", "wb");

    if (file_client != NULL) {
        fwrite(server->clients, sizeof(clients_t),
            server->nb_clients, file_client);
        fclose(file_client);
    }
}

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
    FILE *file_teams = fopen("teams_log", "wb");
    FILE *channel_teams = fopen("channel_log", "wb");
    FILE *thread_teams = fopen("thread_log", "wb");
    FILE *members_teams = fopen("members_log", "wb");

    save_server(server);
    save_client(server);
    if (file_teams != NULL && server->teams != NULL)
        fwrite(server->teams, sizeof(team_t), server->nb_teams, file_teams);
    if (channel_teams != NULL)
        save_teams(server, channel_teams, thread_teams);
    if (members_teams != NULL)
        save_members(server, members_teams);
    fclose(file_teams);
    fclose(thread_teams);
    fclose(channel_teams);
    fclose(members_teams);
}
