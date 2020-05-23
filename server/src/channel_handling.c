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
}

void init_first_thread(server_t *server, int i, int k)
{
    strcpy(server->teams[i].channel[k].thread[0].thread_content, "NULL");
    strcpy(server->teams[i].channel[k].thread[0].thread_title, "NULL");
    strcpy(server->teams[i].channel[k].thread[0].thread_id, "NULL");
}

bool user_subscribed(server_t *server, int i, int id)
{
    for (int k = 0; strcmp(server->teams[i].members[k], "NULL"); k++)
        if (!strcmp(server->teams[i].members[k], server->clients[id].user_name))
            return (true);
    dprintf(server->clients[id].fd_client,
        "533 You can't create a channel if you aren't in the team\r\n");
    return (false);
}

bool channel_exist(server_t *server, int i, char *name, int id)
{
    for (int k = 0; (strcmp(server->teams[i].channel[k].channel_id, "NULL") != 0);
        k++)
        if ((strcmp(server->teams[i].channel[k].channel_name, name) == 0)) {
            dprintf(server->clients[id].fd_client,
                "511 This channel already exist\r\n");
            dprintf(server->clients[id].fd_client, "129|\r\n");
            return (false);
        }
    return (true);
}

void create_new_channel(server_t *server, int id, char *name, char *desc)
{
    int i = 0;
    int k = 0;
    int count = 0;

    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    if (!channel_exist(server, i, name, id) || !user_subscribed(server, i, id))
        return;
    for (; strcmp(server->teams[i].channel[k].channel_id, "NULL"); k++);
    server->teams[i].channel = realloc(server->teams[i].channel,
        sizeof(channel_t) * (k + 2));
    memset(&server->teams[i].channel[k], 0, sizeof(channel_t));
    server->teams[i].channel[k].thread = malloc(sizeof(thread_t));
    strcpy(server->teams[i].channel[k].channel_name, name);
    strcpy(server->teams[i].channel[k].channel_id, generate_id());
    strcpy(server->teams[i].channel[k].channel_desc, desc);
    init_first_thread(server, i, k);
    init_next_channel(server, i, k + 1);
    dprintf(server->clients[id].fd_client,
        "123|%s|%s|%s|\r\n",
        server->teams[i].channel[k].channel_id,
        server->teams[i].channel[k].channel_name,
        server->teams[i].channel[k].channel_desc);
    for (int a = 0; strcmp(server->teams[i].members[a], "NULL") != 0; a++) {
        for (count = 0; strcmp(server->clients[count].user_name,
            server->teams[i].members[a]) != 0; count++);
        dprintf(server->clients[count].fd_client, "106|%s|%s|%s|\r\n",
            server->teams[i].channel[k].channel_id,
            server->teams[i].channel[k].channel_name,
            server->teams[i].channel[k].channel_desc);
    }
    dprintf(server->clients[id].fd_client,
        "226 You succesfully created the channel \"%s\"\r\n",
        server->teams[i].channel[k].channel_name);
    server_event_channel_created(server->teams[i].team_id,
        server->teams[i].channel[k].channel_id,
        server->teams[i].channel[k].channel_name);
    server->teams[i].nb_channel++;
    server->teams[i].channel[k].nb_thread = 0;
}
