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
        server->clients[j].active = false;
        dprintf(server->clients[j].fd_client,
            "221 Service closing control connection\r\n");
    }
    if (file_server != NULL)
        fwrite(server, sizeof(server_t), 1, file_server); 
    fclose(file_server);
}

void save_client(server_t *server)
{
    FILE *file_client = fopen("client_log", "wb");

    if (file_client != NULL) {
        fwrite(server->clients, sizeof(clients_t), server->nb_clients,
            file_client);
        fclose(file_client);
    }
}

void save_teams(server_t *server, FILE *channel_teams, FILE *thread_teams)
{
    for (int i = 0; i < server->nb_teams; i++) {
        if (server->teams[i].channel)
            continue;
        fwrite(server->teams[i].channel, sizeof(channel_t),
            server->teams[i].nb_channel, channel_teams);
        if (thread_teams != NULL)
            for (int a = 0; a < server->teams[i].channel[a].nb_thread; a++)
                fwrite(server->teams[i].channel[a].thread,
                sizeof(server->teams[i].channel[a].thread),
                server->teams[i].channel[a].nb_thread, thread_teams);
    }
}

void save_struct(server_t *server)
{
    FILE *file_teams = fopen("teams_log", "wb");
    FILE *channel_teams = fopen("channel_log", "wb");
    FILE *thread_teams = fopen("thread_log", "wb");

    save_server(server);
    save_client(server);
    if (file_teams != NULL) {
        for (int j = 0; j < server->nb_clients; j++) {
            fwrite(server->teams, sizeof(team_t), server->nb_teams,
                file_teams);
            if (channel_teams != NULL)
                save_teams(server, channel_teams, thread_teams);
        }
    }
    fclose(file_teams);
    fclose(thread_teams);
}