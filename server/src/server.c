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

server_t *read_struct(server_t *server)
{
    FILE *file_server = fopen("server_log", "rb");
    FILE *file_client = fopen("client_log", "rb");
    FILE *file_teams = fopen("teams_log", "rb");

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
    for (int i = 0; i < server->nb_clients; i++)
        server->clients[i].fd_client = 0;

    server->fp = fopen("messages","r");
    if (server->fp != NULL) {
        char *line = NULL;
        size_t len = 0;
        while(getline(&line, &len, server->fp) != -1)
            parse_messages(server, line);
    }

    if (file_teams != NULL) {
        server->clients[0].teams = malloc(2 * sizeof(team_t));
        fread(server->clients[0].teams, sizeof(team_t), 2, file_teams);
        fclose(file_teams);
    }
    return (server);
}

void save_struct(server_t *server)
{
    FILE *file_client = fopen("client_log", "wb");
    FILE *file_server = fopen("server_log", "wb");
    FILE *file_teams = fopen("teams_log", "wb");
    //FILE *channel_teams = fopen("channel_log", "wb");
    //FILE *thread_teams = fopen("thread_log", "wb");

    for (int i = 0; i < server->nb_clients; i++) {
        server->clients[i].active = false;
        dprintf(server->clients[i].fd_client, "deco plz\r\n");
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
        dprintf(1, "%ld\n", fwrite(server->clients[0].teams, sizeof(team_t), 2, file_teams));
        fclose(file_teams);
    }
}

void start_server(char **av)
{
    server_t *server = malloc(sizeof(server_t));
    server->clients = malloc(sizeof(clients_t));

    keepRunning = true;
    server->port = atoi(av[1]);
    init_server(server);
    server = read_struct(server);
    server->fp = fopen("messages","a+");
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
}
