/*
** EPITECH PROJECT, 2020
** read.c
** File description:
** read.c
*/

#include "server.h"

server_t *read_teams(server_t *server, FILE *channel_teams, FILE *thread_teams,
    int i)
{
    if (channel_teams != NULL) {
        server->teams[i].channel = malloc((server->teams[i].nb_channel) *
            sizeof(channel_t));
        fread(server->teams[i].channel, sizeof(channel_t),
            server->teams[i].nb_channel, channel_teams);
    }
    if (thread_teams != NULL) {
        for (int a = 0; a < server->teams[i].nb_channel; a++) {
            server->teams[i].channel[a].thread = malloc(
                (server->teams[i].channel[a].nb_thread) * sizeof(thread_t));
            fread(server->teams[i].channel[a].thread, sizeof(thread_t),
                server->teams[i].channel[a].nb_thread, thread_teams);
        }
    }
    return (server);
}

server_t *init_read(server_t *server)
{
    for (int j = 0; j < server->nb_clients; j++) {
        server_event_user_loaded(server->clients[j].user_id,
            server->clients[j].user_name);
        server->clients[j].use_state = malloc(sizeof(char *) * 4);
        server->clients[j].use_state[0] = NULL;
        server->clients[j].use_state[1] = NULL;
        server->clients[j].use_state[2] = NULL;
        server->clients[j].fd_client = 0;
    }
    return (server);
}

server_t *read_dimensionnal_array(server_t *server)
{
    char *line = NULL;
    size_t len = 0;
    bool first = false;

    server->fp = fopen("messages","r");
    if (server->fp != NULL)
        while (getline(&line, &len, server->fp) != -1)
            parse_messages(server, line);
    server->comments = fopen("comments","r");
    if (server->comments != NULL) {
        line = NULL;
        len = 0;
        while (getline(&line, &len, server->comments) != -1) {
            parse_comments(server, line, first);
            if (first == false)
                first = !first;
        }
    }
    return (server);
}

server_t *read_struct(server_t *server)
{
    FILE *file_teams = fopen("teams_log", "rb");
    FILE *channel_teams = fopen("channel_log", "rb");
    FILE *thread_teams = fopen("thread_log", "rb");

    server = read_server(server);
    server = read_client(server);
    server = init_read(server);
    if (file_teams != NULL) {
        server->teams = malloc((server->nb_teams) * sizeof(team_t));
        fread(server->teams, sizeof(team_t), server->nb_teams,
            file_teams);
        if (channel_teams != NULL)
            for (int i = 0; i < server->nb_teams; i++)
                server = read_teams(server, channel_teams, thread_teams, i);
    }
    if (file_teams != NULL && channel_teams != NULL && thread_teams != NULL) {
        printf("%s\r\n", server->teams[0].channel[0].thread[0].thread_title);
        fclose(file_teams);
        fclose(channel_teams);
        fclose(thread_teams);
    }
    server = read_dimensionnal_array(server);
    return (server);
}
