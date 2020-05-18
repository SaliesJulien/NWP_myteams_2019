/*
** EPITECH PROJECT, 2020
** read.c
** File description:
** read.c
*/

#include "server.h"

server_t *parse_messages(server_t *server, char *command)
{
    char *receiver = strtok(command, "|");
    char *sender = strtok(NULL, "|");
    char *message = strtok(NULL, "|");

    server->clients[uuid_index(server, sender)].conversation =
        malloc(sizeof(messages_t));
    server->clients[uuid_index(server, receiver)].conversation =
        malloc(sizeof(messages_t));
    fill_messages(server, uuid_index(server, sender), receiver, message);
    return (server);
}

server_t *parse_comments(server_t *server, char *command, bool first)
{
    char *team = strtok(command, "|");
    char *channel = strtok(NULL, "|");
    char *thread = strtok(NULL, "|");
    char *message = strtok(NULL, "|");
    int a = 0;
    int b = 0;
    int c = 0;
    int count = 0;

    for (int i = 0; i < server->nb_teams; i++)
        if (strcmp(server->teams[i].team_id, team) == 0)
            a = i;
    for (int i = 0; i < server->teams[a].nb_channel; i++)
        if (strcmp(server->teams[a].channel[i].channel_id, channel) == 0)
            b = i;
    for (int i = 0; i < server->teams[a].channel[b].nb_thread; i++)
        if (strcmp(server->teams[a].channel[b].thread[i].thread_id,
            thread) == 0)
            c = i;
    if (first == false) {
        server->teams[a].channel[b].thread[c].comment = malloc(
            sizeof(char *) * 2);
        server->teams[a].channel[b].thread[c].comment[0] = malloc(
            sizeof(char *) * strlen(message));
        strcpy(server->teams[a].channel[b].thread[c].comment[0], message);
        strcpy(server->teams[a].channel[b].thread[c].comment[1], "NULL");
    } else {
        for (; strcmp(server->teams[a].channel[b].thread[c].comment[count],
            "NULL"); count++);
        server->teams[a].channel[b].thread[c].comment = realloc(
            server->teams[a].channel[b].thread[c].comment, (sizeof(char *) *
            (count + 2)));
        server->teams[a].channel[b].thread[c].comment[count] = malloc(
            sizeof(char) * strlen(message));
        strcpy(server->teams[a].channel[b].thread[c].comment[count], message);
        strcpy(server->teams[a].channel[b].thread[c].comment[count + 1], "NULL");
    }
    return (server);
}

server_t *read_server(server_t *server)
{
    FILE *file_server = fopen("server_log", "rb");

    if (file_server != NULL) {
        server = malloc(sizeof(server_t));
        fread(server, sizeof(server_t), 1, file_server);
        fclose(file_server);
    }
    return (server);
}

server_t * read_client(server_t *server)
{
    FILE *file_client = fopen("client_log", "rb");

    if (file_client != NULL) {
        server->clients = malloc(server->nb_clients * sizeof(clients_t));
        fread(server->clients, sizeof(clients_t), server->nb_clients,
            file_client);
        fclose(file_client);
    }
    return (server);
}

server_t *read_teams(server_t *server, FILE *channel_teams, FILE *thread_teams,
    int i)
{
    server->teams[i].channel = malloc( (server->teams[i].nb_channel + 1) *
        sizeof(channel_t));
    fread(server->teams[i].channel, sizeof(channel_t),
        (server->teams[i].nb_channel + 1), channel_teams);
    for (int a = 0; a < server->teams[i].channel[a].nb_thread; a++) {
        server->teams[i].channel[a].thread = malloc(
            (server->teams[i].channel[a].nb_thread + 1) * sizeof(thread_t));
        fread(server->teams[i].channel[a].thread, sizeof(thread_t),
            (server->teams[i].channel[a].nb_thread + 1), thread_teams);
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
        server->teams = malloc((server->nb_teams + 1) * sizeof(team_t));
        fread(server->teams, sizeof(team_t), (server->nb_teams + 1),
            file_teams);
        if (channel_teams != NULL)
            for (int i = 0; i < server->nb_teams; i++)
                if (thread_teams != NULL)
                    server = read_teams(server, channel_teams, thread_teams,
                        i);
    }
    if (file_teams != NULL && channel_teams != NULL && thread_teams != NULL) {
        fclose(file_teams);
        fclose(channel_teams);
        fclose(thread_teams);
    }
    server = read_dimensionnal_array(server);
    return (server);
}