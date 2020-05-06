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
        FD_SET(server->clients[i].fd_client, &server->set[READING]);
        FD_SET(server->clients[i].fd_client, &server->set[WRITING]);
    }
}

void read_struct(server_t *server)
{
    FILE *file = fopen("output", "rb");

    if (file != NULL) {
        fread(server, sizeof(server_t), 1, file);
        fclose(file);
    }
}

void save_struct(server_t *server)
{
    FILE *file = fopen("output", "wb");

    if (file != NULL) {
        fwrite(server, sizeof(server_t), 1, file);
        fclose(file);
    }
}

void start_server(char **av)
{
    server_t *server = malloc(sizeof(server_t));
    server->clients = malloc(sizeof(clients_t));

    keepRunning = true;
    server->port = atoi(av[1]);
    init_server(server);
    read_struct(server);
    while (true) {
        dprintf(1, "1\n");
        init_sets(server);
        signal(SIGINT, control_c);
        if (keepRunning == false) {
            save_struct(server);
            break;
        }
        dprintf(1, "2\n");
        if ((select(FD_SETSIZE, &server->set[READING],
            &server->set[WRITING], NULL, NULL)) == -1)
            break;
        dprintf(1, "3\n");
        reading(server);
        dprintf(1, "4\n");
    }
    free(server);
    free(server->clients);
}
