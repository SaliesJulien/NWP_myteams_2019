/*
** EPITECH PROJECT, 2020
** read.c
** File description:
** read.c
*/

#include "server.h"

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

server_t *read_messages(server_t *server)
{
    char *line = NULL;
    size_t len = 0;
    FILE *messages_write = fopen("messages", "r");

    if (messages_write != NULL) {
        while (getline(&line, &len, messages_write) != -1)
            parse_messages(server, line);
    }
    free(line);
    if (messages_write != NULL)
        fclose(messages_write);
    return (server);
}

server_t *read_contents(server_t *server)
{
    char *line = NULL;
    size_t len = 0;
    bool first = false;
    FILE *comment_write = fopen("comments", "r");

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
    if (comment_write != NULL)
        fclose(comment_write);
    return (server);
}

server_t *read_opps(server_t *server, FILE *file_teams, FILE *channel_teams)
{
    FILE *thread_teams = fopen("thread_log", "rb");
    FILE *members_teams = fopen("members_log", "rb");

    if (file_teams != NULL && channel_teams != NULL && thread_teams != NULL
        && members_teams != NULL) {
        server->teams = malloc((server->nb_teams + 1) * sizeof(team_t));
        fread(server->teams, sizeof(team_t), server->nb_teams,
            file_teams);
        strcpy(server->teams[server->nb_teams].team_id, "NULL");
        for (int i = 0; i < server->nb_teams; i++) {
            server = read_teams(server, channel_teams, thread_teams, i);
            server = read_members(server, members_teams, i);
        }
    }
    if (thread_teams != NULL && members_teams != NULL) {
        fclose(thread_teams);
        fclose(members_teams);
    }
    return (server);
}

server_t *read_struct(server_t *server)
{
    FILE *file_teams = fopen("teams_log", "rb");
    FILE *channel_teams = fopen("channel_log", "rb");

    server = read_server(server);
    server = read_client(server);
    server = init_read(server);
    server = read_opps(server, file_teams, channel_teams);
    if (file_teams != NULL && channel_teams != NULL) {
        fclose(file_teams);
        fclose(channel_teams);
    }
    server = read_messages(server);
    server = read_contents(server);
    return (server);
}
