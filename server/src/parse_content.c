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
    find_good_comments(server->teams[a].channel[b].thread[c], message, first);
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

server_t *read_client(server_t *server)
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