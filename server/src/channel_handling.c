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

bool channel_exist(server_t *server, int i, char *name, int id)
{
    for (int k = 0; strcmp(server->teams[i].channel[k].channel_id, "NULL");
        k++)
        if (!strcmp(server->teams[i].channel[k].channel_name, name)) {
            dprintf(server->clients[id].fd_client,
                "511 This channel already exist\n");
            return (false);
        }
    return (true);
}

void create_new_channel(server_t *server, int id, char *name, char *desc)
{
    int i = 0;
    int k = 0;

    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    if (!channel_exist(server, i, name, id))
        return;
    for (; strcmp(server->teams[i].channel[k].channel_id, "NULL"); k++);
    server->teams[i].channel = realloc(server->teams[i].channel,
        sizeof(channel_t) * (k + 2));
    server->teams[i].channel[k].thread = malloc(sizeof(thread_t));
    strcpy(server->teams[i].channel[k].channel_name, name);
    strcpy(server->teams[i].channel[k].channel_id, generate_id());
    strcpy(server->teams[i].channel[k].channel_desc, desc);
    init_first_thread(server, i, k);
    init_next_channel(server, i, k + 1);
    dprintf(server->clients[id].fd_client,
        "221 You succesfully created the channel \"%s\"\n",
        server->teams[i].channel[k].channel_name);
    server->teams[i].nb_channel++;
}