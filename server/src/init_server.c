/*
** EPITECH PROJECT, 2020
** init_server.c
** File description:
** init_server.c
*/

#include "server.h"

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

void init_teams(server_t *server)
{
    if(access("teams_log", F_OK) == -1) {
        server->teams = malloc(sizeof(team_t));
        memset(server->teams, 0, sizeof(team_t));
        strcpy(server->teams[0].team_id, "NULL");
        strcpy(server->teams[0].team_desc, "NULL");
        strcpy(server->teams[0].team_name, "NULL");
    }
    if(access("client_log", F_OK) == -1) {
        server->clients = malloc(sizeof(clients_t));
        memset(server->clients, 0, sizeof(clients_t));
    }
    server->command = NULL;
}

server_t *server_init(server_t *server, char **av)
{
    init_teams(server);
    keepRunning = true;
    server->port = atoi(av[1]);
    start_connection(server);
    server = read_struct(server);
    server->messages_write = fopen("messages","a+");
    server->comment_write = fopen("comments","a+");
    return (server);
}

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