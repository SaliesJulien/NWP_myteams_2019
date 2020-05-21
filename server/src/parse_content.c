/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** parse_content
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

void find_good_comments(thread_t thread, char *message, bool first)
{
    int count = 0;

    if (first == false) {
        thread.comment = malloc(sizeof(char *) * 2);
        thread.comment[0] = malloc(sizeof(char *) * strlen(message));
        strcpy(thread.comment[0], message);
        strcpy(thread.comment[1], "NULL");
    } else {
        for (; strcmp(thread.comment[count], "NULL"); count++);
        thread.comment = realloc(thread.comment, (sizeof(char *) *
            (count + 2)));
        thread.comment[count] = malloc(sizeof(char) * strlen(message));
        strcpy(thread.comment[count], message);
        strcpy(thread.comment[count + 1], "NULL");
    }
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
        server->teams[a].channel[b].thread[c].comment = malloc(sizeof(char *) * 2);
        server->teams[a].channel[b].thread[c].comment[0] = malloc(sizeof(char *) * strlen(message));
        strcpy(server->teams[a].channel[b].thread[c].comment[0], message);
        strcpy(server->teams[a].channel[b].thread[c].comment[1], "NULL");
    } else {
        for (; strcmp(server->teams[a].channel[b].thread[c].comment[count], "NULL"); count++);
        server->teams[a].channel[b].thread[c].comment = realloc(server->teams[a].channel[b].thread[c].comment, (sizeof(char *) *
            (count + 2)));
        server->teams[a].channel[b].thread[c].comment[count] = malloc(sizeof(char) * strlen(message));
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
        fread(server, sizeof(server), 1, file_server);
        fclose(file_server);
    }
    return (server);
}

server_t *read_client(server_t *server)
{
    FILE *file_client = fopen("client_log", "rb");

    if (file_client != NULL) {
        server->clients = malloc(server->nb_clients * sizeof(clients_t));
        fread(server->clients, sizeof(server->clients), server->nb_clients,
            file_client);
        fclose(file_client);
    }
    return (server);
}