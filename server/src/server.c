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

void free_server(server_t *server, int i)
{
    for (int j = 0; j < 3; j++)
        free(server->clients[i].use_state[j]);
    free(server->clients[i].use_state);
    for (int a = 0; a < server->clients[i].nb_conversation; a++) {
        free(server->clients[i].conversation[a].client_id);
        for (int j = 0; j < server->clients[i].conversation[a].nb_messages; j++)
            free(server->clients[i].conversation[a].message[j]);
        free(server->clients[i].conversation[a].message);
    }
    if (server->clients[i].nb_conversation > 0)
        free(server->clients[i].conversation);
}

void free_thread(server_t *server, int i, int j)
{
    for (int k = 0; k < server->teams[i].channel[j].nb_thread; k++) {
        for (int m = 0;
            m < server->teams[i].channel[j].thread[k].nb_comments + 1; m++)
            free(server->teams[i].channel[j].thread[k].comment[m]);
        free(server->teams[i].channel[j].thread[k].comment);
    }
    free(server->teams[i].channel[j].thread);
}

void free_all(server_t *server)
{
    for (int i = 0; i < server->nb_clients; i++)
        free_server(server, i);
    for (int i = 0; i < server->nb_teams; i++) {
        free(server->teams[i].members);
        for (int j = 0; j < server->teams[i].nb_channel; j++)
            free_thread(server, i, j);
        free(server->teams[i].channel);
    }
    free(server->teams);
    free(server->clients);
    free(server);
}

void start_server(char **av)
{
    server_t *server = malloc(sizeof(server_t));

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
    fclose(server->messages_write);
    fclose(server->comment_write);
    free_all(server);
}
