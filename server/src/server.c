/*
** EPITECH PROJECT, 2020
** server.c
** File description:
** server.c
*/

#include "server.h"

void start_connection(server_t *server)
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
    server->nb_clients = 0;
    server->nb_teams = 0;
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

void init_teams(server_t *server)
{
    server->command = NULL;
    server->teams = malloc(sizeof(team_t));
    strcpy(server->teams[0].team_id, "NULL");
    strcpy(server->teams[0].team_desc, "NULL");
    strcpy(server->teams[0].team_name, "NULL");
    server->teams[0].nb_channel = 0;
    server->teams[0].members = NULL;
    server->teams[0].channel = NULL;
}

server_t *server_init(server_t *server, char **av)
{
    init_teams(server);
    keepRunning = true;
    server->port = atoi(av[1]);
    start_connection(server);
    server = read_struct(server);
    server->fp = fopen("messages","a+");
    server->comments = fopen("comments","a+");
    return (server);
}

void start_server(char **av)
{
    server_t *server = malloc(sizeof(server_t));
    server->clients = malloc(sizeof(clients_t));

    memset(server->clients, 0, sizeof(clients_t));
    server = server_init(server, av);
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
    fclose(server->fp);
    fclose(server->comments);
    free(server->teams);
    free(server->clients);
    free(server);
}
