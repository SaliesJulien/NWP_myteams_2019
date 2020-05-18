/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** read_client
*/

#include "server.h"

void new_clients(server_t *server)
{
    int fd = 0;
    socklen_t len_cin = sizeof(server->inf);

    fd = accept(server->fd_server, (struct sockaddr *)&server->inf, &len_cin);
    if (fd == -1)
        printf("connection with new user failed");
    else
        new_client_struct(server, fd);
    dprintf(server->clients[server->nb_clients].fd_client,
        "220 Service ready for new user\r\n");
    server->nb_clients++;
}

void remove_client(server_t *server, int client, int id)
{
    if (strcmp(server->command, "/logout\r\n") == 0) {
        dprintf(client, "221 Service closing control connection\r\n");
        if (server->clients[id].logged == false) {
            while (id + 1 < server->nb_clients) {
                server->clients[id] = server->clients[id + 1];
                id++;
            }
            server->nb_clients--;
        }
        else
            server->clients[id].active = false;
        printf("Client disconnected\r\n");
    } else {
        dprintf(client, "501 Error syntax in parameters or arguments\r\n");
    }
}

void old_clients(server_t *server, int client)
{
    for (int i = 0; i < server->nb_clients; i++) {
        if (server->clients[i].fd_client == client) {
            server->command = calloc(DEFAULT_BODY_LENGTH, sizeof(char));
            read(server->clients[i].fd_client, server->command, DEFAULT_BODY_LENGTH);
            exec_commands(server, server->clients[i].fd_client, i);
        }
    }
}

void manage(server_t *server, int i)
{
    if (i == server->fd_server)
        new_clients(server);
    else
        old_clients(server, i);
}

void reading(server_t *server)
{
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (FD_ISSET(i, &server->set[READING]) == true) {
            manage(server, i);
        }
    }
}
