/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

void init_next_channel(server_t *server, int id, int i, int k)
{
    strcpy(server->clients[id].teams[i].channel[k].channel_name, "NULL");
    strcpy(server->clients[id].teams[i].channel[k].channel_desc, "NULL");
    strcpy(server->clients[id].teams[i].channel[k].channel_id, "NULL");
    server->clients[id].teams[i].channel[k].thread = NULL;
}

void print_channel(server_t *server, int id, int client)
{
    int i = 0;

    for (i = 0; strcmp(server->clients[id].teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (int j = 0; strcmp(server->clients[id].teams[i].channel[j].channel_id,
    "NULL") != 0; j++) {
        dprintf(client, "%s\n",
            server->clients[id].teams[i].channel[j].channel_id);
    }
}

void save_channel_infos(channel_t *channel, char *name, char *desc)
{
    strcpy(channel->channel_id, generate_id());
    strcpy(channel->channel_name, name);
    strcpy(channel->channel_desc, desc);
}

void create_new_channel(server_t *server, int id, char *name, char *desc)
{
    int i = 0;
    int k = 0;

    for (i = 0; strcmp(server->clients[id].teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (; strcmp(server->clients[id].teams[i].channel[k].channel_id, "NULL")
    != 0; k++);
    server->clients[id].teams[i].channel =
        realloc(server->clients[id].teams[i].channel,
            sizeof(channel_t) * (k + 2));
    server->clients[id].teams[i].channel[k].thread = malloc(sizeof(thread_t));
    init_next_thread(server->clients[id], i, k, 0);
    save_channel_infos(&server->clients[id].teams[i].channel[k], name, desc);
    dprintf(server->clients[id].fd_client, "New channel \"%s\" created.\n",
            server->clients[id].teams[i].channel[k].channel_id);
    init_next_channel(server, id, i, k + 1);
}