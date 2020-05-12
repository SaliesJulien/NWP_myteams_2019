/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

void init_next_thread(clients_t client, int i, int k, int j)
{
    strcpy(client.teams[i].channel[k].thread[j].thread_content, "NULL");
    strcpy(client.teams[i].channel[k].thread[j].thread_title, "NULL");
    strcpy(client.teams[i].channel[k].thread[j].thread_id, "NULL");
}

void set_next_thread(thread_t *thread, char *name, char *desc)
{
    thread->comment = malloc(sizeof(char *));
    strcpy(thread->thread_id, generate_id());
    strcpy(thread->thread_title, name);
    strcpy(thread->thread_content, desc);
}

void create_new_thread(server_t *server, int id, char *name, char *desc)
{
    int i = 0;
    int k = 0;
    int j = 0;

    for (i = 0; strcmp(server->clients[id].teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (k = 0; strcmp(server->clients[id].teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]); k++);
    for (j = 0; strcmp(
        server->clients[id].teams[i].channel[k].thread[j].thread_id, "NULL")
        != 0; j++);
    server->clients[id].teams[i].channel[k].thread =
        realloc(server->clients[id].teams[i].channel[k].thread,
        sizeof(channel_t) * (j + 2));
    set_next_thread(&server->clients[id].teams[i].channel[k].thread[j],
        name, desc);
    dprintf(server->clients[id].fd_client, "New thread \"%s\" created.\n",
            server->clients[id].teams[i].channel[k].thread[j].thread_id);
    init_next_thread(server->clients[id], i, k, j + 1);
}