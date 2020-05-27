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
        server->teams[i].channel = malloc((server->teams[i].nb_channel + 1) *
            sizeof(channel_t));
        fread(server->teams[i].channel, sizeof(channel_t),
            server->teams[i].nb_channel, channel_teams);
        strcpy(server->teams[i].channel[server->teams[i].nb_channel].channel_id, "NULL");
    }
    if (thread_teams != NULL) {
        for (int a = 0; a < server->teams[i].nb_channel; a++) {
            server->teams[i].channel[a].thread = malloc(
                (server->teams[i].channel[a].nb_thread + 1) * sizeof(thread_t));
            fread(server->teams[i].channel[a].thread, sizeof(thread_t),
                server->teams[i].channel[a].nb_thread, thread_teams);
            strcpy(server->teams[i].channel[a].thread[server->teams[i].channel[a].nb_thread].thread_id, "NULL");
        }
    }
    return (server);
}

server_t *read_members(server_t *server, FILE *members_teams, int i)
{
    if (members_teams != NULL) {
        server->teams[i].members = malloc((server->teams[i].nb_members + 1) *
            sizeof(members_t));
        fread(server->teams[i].members, sizeof(members_t),
            server->teams[i].nb_members, members_teams);
        strcpy(server->teams[i].members[server->teams[i].nb_members].name, "NULL");
        strcpy(server->teams[i].members[server->teams[i].nb_members].id, "NULL");
    }
    return (server);
}

server_t *init_read(server_t *server)
{
    for (int j = 0; j < server->nb_clients; j++) {
        server_event_user_loaded(server->clients[j].user_id,
            server->clients[j].user_name);
        server->clients[j].use_state = malloc(sizeof(char *) * 3);
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
    FILE *messages_write = fopen("messages","r");
    FILE *comment_write = fopen("comments","r");

    if (messages_write != NULL) {
        while (getline(&line, &len, messages_write) != -1)
            parse_messages(server, line);
    }
    free(line);
    if (comment_write != NULL) {
        line = NULL;
        len = 0;
        while (getline(&line, &len, comment_write) != -1) {
            parse_comments(server, line, first);
            if (first == false)
                first = !first;
        }
    }
    free(line);
    if (messages_write != NULL)
        fclose(messages_write);
    if (comment_write != NULL)
        fclose(comment_write);
    return (server);
}

server_t *read_struct(server_t *server)
{
    FILE *file_teams = fopen("teams_log", "rb");
    FILE *channel_teams = fopen("channel_log", "rb");
    FILE *thread_teams = fopen("thread_log", "rb");
    FILE *members_teams = fopen("members_log", "rb");

    server = read_server(server);
    server = read_client(server);
    server = init_read(server);
    if (file_teams != NULL) {
        server->teams = malloc((server->nb_teams + 1) * sizeof(team_t));
        fread(server->teams, sizeof(team_t), server->nb_teams,
            file_teams);
        strcpy(server->teams[server->nb_teams].team_id, "NULL");
        if (channel_teams != NULL)
            for (int i = 0; i < server->nb_teams; i++) {
                server = read_teams(server, channel_teams, thread_teams, i);
                server = read_members(server, members_teams, i);
            }
    }
    if (file_teams != NULL && channel_teams != NULL && thread_teams != NULL) {
        fclose(file_teams);
        fclose(channel_teams);
        fclose(thread_teams);
    }
    server = read_dimensionnal_array(server);
    return (server);
}
