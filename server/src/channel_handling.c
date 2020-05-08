/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

void init_next_channel(server_t *server, int id, int i, int k)
{
    server->clients[id].teams[i].channel[k].channel_name = NULL;
    server->clients[id].teams[i].channel[k].channel_desc = NULL;
    server->clients[id].teams[i].channel[k].channel_id = NULL;
    server->clients[id].teams[i].channel[k].thread = NULL;
}

void print_channel(server_t *server, int id, int client)
{
    int i = 0;

    for (i = 0; strcmp(server->clients[id].teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (int j = 0; server->clients[id].teams[i].channel[j].channel_id
        != NULL; j++) {
        dprintf(client, "%s\n",
            server->clients[id].teams[i].channel[j].channel_id);
    }
}

/*void save_channel_infos(server_t *server, int id, int i, int k)
{
}*/

void create_new_channel(server_t *server, int id, char *name, char *desc)
{
    int i = 0;
    int k = 0;

    for (i = 0; strcmp(server->clients[id].teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (; server->clients[id].teams[i].channel[k].channel_id != NULL; k++);
    server->clients[id].teams[i].channel =
        realloc(server->clients[id].teams[i].channel,
            sizeof(channel_t) * (k + 2));
    server->clients[id].teams[i].channel[k].channel_id =
        malloc(sizeof(char) * 37);
    server->clients[id].teams[i].channel[k].channel_name =
        malloc(sizeof(char) * strlen(name));
    server->clients[id].teams[i].channel[k].channel_desc =
        malloc(sizeof(char) * strlen(desc));
    server->clients[id].teams[i].channel[k].thread = malloc(sizeof(thread_t));
    init_next_thread(server->clients[id], i, k, 0);
    strcpy(server->clients[id].teams[i].channel[k].channel_id, generate_id());
    strcpy(server->clients[id].teams[i].channel[k].channel_name, name);
    strcpy(server->clients[id].teams[i].channel[k].channel_desc, desc);
    dprintf(server->clients[id].fd_client, "New channel \"%s\" created.\n",
            server->clients[id].teams[i].channel[k].channel_id);
    init_next_channel(server, id, i, k + 1);
}