/*
** EPITECH PROJECT, 2020
** server.c
** File description:
** server.c
*/

#include "server.h"

void init_server(server_t *server)
{
    int option = 1;
    socklen_t len = sizeof(server->inf);

    if ((server->fd_server = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket failed");
        exit(84);
    }
    setsockopt(server->fd_server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
        &option, sizeof(int));
    server->inf.sin_addr.s_addr = htonl(INADDR_ANY);
    server->inf.sin_port = htons(server->port);
    server->inf.sin_family = AF_INET;
    if (bind(server->fd_server, (struct sockaddr *)&server->inf, len) == -1)
        exit(84);
    if (listen(server->fd_server, MAX_CLIENT) == -1)
        exit(84);
}

void init_sets(server_t *server)
{
    FD_ZERO(&server->set[READING]);
    FD_ZERO(&server->set[WRITING]);
    FD_SET(server->fd_server, &server->set[READING]);
    FD_SET(server->fd_server, &server->set[WRITING]);
    for (int i = 0; i < server->nb_clients; i++) {
        if (server->clients[i].active == true) {
            FD_SET(server->clients[i].fd_client, &server->set[READING]);
            FD_SET(server->clients[i].fd_client, &server->set[WRITING]);
        }
    }
}

void parse_messages(server_t *server, char *command)
{
    char *receiver = strtok(command, "|");
    char *sender = strtok(NULL, "|");
    char *message = strtok(NULL, "|");

    server->clients[uuid_index(server, sender)].conversation = malloc(sizeof(messages_t));
    server->clients[uuid_index(server, receiver)].conversation = malloc(sizeof(messages_t));
    fill_messages(server, uuid_index(server, sender), receiver, message);
}

void parse_comments(server_t *server, char *command, bool first)
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
        for (; strcmp(server->teams[a].channel[b].thread[c].comment[count], "NULL")
            ; count++);
        server->teams[a].channel[b].thread[c].comment = realloc(
            server->teams[a].channel[b].thread[c].comment, (sizeof(char *) *
            (count + 2)));
        server->teams[a].channel[b].thread[c].comment[count] = malloc(
            sizeof(char) * strlen(message));
        strcpy(server->teams[a].channel[b].thread[c].comment[count], message);
        strcpy(server->teams[a].channel[b].thread[c].comment[count + 1], "NULL");
    }
}

server_t *read_struct(server_t *server)
{
    FILE *file_server = fopen("server_log", "rb");
    FILE *file_client = fopen("client_log", "rb");
    FILE *file_teams = fopen("teams_log", "rb");
    FILE *channel_teams = fopen("channel_log", "rb");
    FILE *thread_teams = fopen("thread_log", "rb");

    if (file_server != NULL) {
        server = malloc(sizeof(server_t));
        fread(server, sizeof(server_t), 1, file_server);
        fclose(file_server);
    }
    if (file_client != NULL) {
        server->clients = malloc(server->nb_clients * sizeof(clients_t));
        fread(server->clients, sizeof(clients_t), server->nb_clients, file_client);
        fclose(file_client);
    }
    for (int j = 0; j < server->nb_clients; j++) {
        server->clients[j].use_state = malloc(sizeof(char*) * 3);
        server->clients[j].use_state[0] = NULL;
        server->clients[j].use_state[1] = NULL;
        server->clients[j].use_state[2] = NULL;
        server->clients[j].fd_client = 0;
    }
    if (file_teams != NULL) {
        server->teams = malloc((server->nb_teams + 1) * sizeof(team_t));
        fread(server->teams, sizeof(team_t), (server->nb_teams + 1), file_teams);
        if (channel_teams != NULL) {
            for (int i = 0; i < server->nb_teams; i++) {
                server->teams[i].channel = malloc((server->teams[i].nb_channel + 1) * sizeof(channel_t));
                fread(server->teams[i].channel, sizeof(channel_t), (server->teams[i].nb_channel + 1), channel_teams);
                if (thread_teams != NULL) {
                    for (int a = 0; a < server->teams[i].channel[a].nb_thread; a++) {
                        server->teams[i].channel[a].thread = malloc((server->teams[i].channel[a].nb_thread + 1) * sizeof(thread_t));
                        fread(server->teams[i].channel[a].thread, sizeof(thread_t), (server->teams[i].channel[a].nb_thread + 1), thread_teams);
                    }
                }
            }
        }
    }
    if (file_teams != NULL)
        fclose(file_teams);
    if (channel_teams != NULL)
        fclose(channel_teams);
    if (thread_teams != NULL)
        fclose(thread_teams);

    server->fp = fopen("messages","r");
    if (server->fp != NULL) {
        char *line = NULL;
        size_t len = 0;
        while (getline(&line, &len, server->fp) != -1)
            parse_messages(server, line);
    }
    server->comments = fopen("comments","r");
    if (server->comments != NULL) {
        char *line = NULL;
        size_t len = 0;
        bool first = false;
        while (getline(&line, &len, server->comments) != -1) {
            parse_comments(server, line, first);
            if (first == false)
                first = !first;
        }
    }
    return (server);
}

void save_struct(server_t *server)
{
    FILE *file_client = fopen("client_log", "wb");
    FILE *file_server = fopen("server_log", "wb");
    FILE *file_teams = fopen("teams_log", "wb");
    FILE *channel_teams = fopen("channel_log", "wb");
    FILE *thread_teams = fopen("thread_log", "wb");

    for (int j = 0; j < server->nb_clients; j++) {
        server->clients[j].active = false;
        dprintf(server->clients[j].fd_client, "deco plz\r\n");
    }
    if (file_server != NULL) {
        fwrite(server, sizeof(server_t), 1, file_server);
        fclose(file_server);
    }
    if (file_client != NULL) {
        fwrite(server->clients, sizeof(clients_t), server->nb_clients, file_client);
        fclose(file_client);
    }
    if (file_teams != NULL) {
        for (int j = 0; j < server->nb_clients; j++) {
            fwrite(server->teams, sizeof(team_t), (server->nb_teams + 1), file_teams);
            if (channel_teams != NULL) {
                for (int i = 0; i < server->nb_teams; i++) {
                    fwrite(server->teams[i].channel, sizeof(channel_t), (server->teams[i].nb_channel + 1), channel_teams);
                    if (thread_teams != NULL) {
                        for (int a = 0; a < server->teams[i].channel[a].nb_thread; a++)
                            fwrite(server->teams[i].channel[a].thread, sizeof(thread_t), (server->teams[i].channel[a].nb_thread + 1), thread_teams);
                    }
                }
            }
        }
        fclose(file_teams);
        if (channel_teams != NULL)
            fclose(channel_teams);
        if (thread_teams != NULL)
            fclose(thread_teams);
    }
}

void init_teams(server_t *server)
{
    server->teams = malloc(sizeof(team_t));
    strcpy(server->teams[0].team_id, "NULL");
    strcpy(server->teams[0].team_desc, "NULL");
    strcpy(server->teams[0].team_name, "NULL");
}

void start_server(char **av)
{
    server_t *server = malloc(sizeof(server_t));
    server->clients = malloc(sizeof(clients_t));

    init_teams(server);
    keepRunning = true;
    server->port = atoi(av[1]);
    init_server(server);
    server = read_struct(server);
    server->fp = fopen("messages","a+");
    server->comments = fopen("comments","a+");
    while (true) {
        init_sets(server);
        signal(SIGINT, control_c);
        if (keepRunning == false) {
            save_struct(server);
            break;
        }
        if ((select(FD_SETSIZE, &server->set[READING],
            &server->set[WRITING], NULL, NULL)) == -1)
            break;
        reading(server);
    }
    free(server);
    free(server->clients);
    fclose(server->fp);
    fclose(server->comments);
}
