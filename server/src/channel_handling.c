/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

void init_next_channel(server_t *server, int i, int k)
{
    strcpy(server->teams[i].channel[k].channel_name, "NULL");
    strcpy(server->teams[i].channel[k].channel_desc, "NULL");
    strcpy(server->teams[i].channel[k].channel_id, "NULL");
    server->teams[i].channel[k].thread = NULL;
}

void init_first_thread(server_t *server, int i, int k)
{
    strcpy(server->teams[i].channel[k].thread[0].thread_content, "NULL");
    strcpy(server->teams[i].channel[k].thread[0].thread_title, "NULL");
    strcpy(server->teams[i].channel[k].thread[0].thread_id, "NULL");
}

void create_new_channel(server_t *server, int id, char *name, char *desc)
{
    int i = 0;
    int k = 0;

    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (; strcmp(server->teams[i].channel[k].channel_id, "NULL"); k++);
    server->teams[i].channel = realloc(server->teams[i].channel,
        sizeof(channel_t) * (k + 2));
    server->teams[i].channel[k].thread = malloc(sizeof(thread_t));
    strcpy(server->teams[i].channel[k].channel_name, name);
    strcpy(server->teams[i].channel[k].channel_id, generate_id());
    strcpy(server->teams[i].channel[k].channel_desc, desc);
    init_first_thread(server, i, k);
    init_next_channel(server, i, k + 1);
    dprintf(server->clients[id].fd_client, "New channel \"%s\" created.\n",
            server->teams[i].channel[k].channel_id);
}