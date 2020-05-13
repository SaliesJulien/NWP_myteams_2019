/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

void init_next_thread(server_t *server, int i, int k, int j)
{
    strcpy(server->teams[i].channel[k].thread[j].thread_content, "NULL");
    strcpy(server->teams[i].channel[k].thread[j].thread_title, "NULL");
    strcpy(server->teams[i].channel[k].thread[j].thread_id, "NULL");
}

void init_first_comment(server_t *server, int i, int k, int j)
{
    server->teams[i].channel[k].thread[j].comment[0] = malloc(sizeof(char) * 5);
    strcpy(server->teams[i].channel[k].thread[j].comment[0], "NULL");
}

void create_new_thread(server_t *server, int id, char *name, char *desc)
{
    int i = 0;
    int k = 0;
    int j = 0;

    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (k = 0; strcmp(server->teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]); k++);
    for (j = 0; strcmp(server->teams[i].channel[k].thread[j].thread_id,
        "NULL"); j++);
    server->teams[i].channel[k].thread =
        realloc(server->teams[i].channel[k].thread,
        sizeof(thread_t) * (j + 2));
    server->teams[i].channel[k].thread[j].comment = malloc(sizeof(char *));
    strcpy(server->teams[i].channel[k].thread[j].thread_id, generate_id());
    strcpy(server->teams[i].channel[k].thread[j].thread_title, name);
    strcpy(server->teams[i].channel[k].thread[j].thread_content, desc);
    init_first_comment(server, i, k, j);
    dprintf(server->clients[id].fd_client, "New thread \"%s\" created.\n",
    server->teams[i].channel[k].thread[j].thread_id);
    init_next_thread(server, i, k, j + 1);
    server->teams[i].channel[k].nb_thread++;
}