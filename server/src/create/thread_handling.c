/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

bool thread_already_exist(channel_t channel, char *name, server_t *server,
    int id)
{
    int j = 0;

    for (j = 0; strcmp(channel.thread[j].thread_id,
        "NULL"); j++)
        if (!strcmp(channel.thread[j].thread_title, name)) {
            dprintf(server->clients[id].fd_client,
                "512 This thread already exist\r\n");
            delay(1);
            dprintf(server->clients[id].fd_client, "129|\r\n");
            return (false);
        }
    return (true);
}

void call_client_lib(server_t *server, int id, int i, int j)
{
    int k = 0;

    for (k = 0; strcmp(server->teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]); k++);
    init_next_thread(server, i, k, j + 1);
    dprintf(server->clients[id].fd_client,
        "124|%s|%s|%s|%s|%s|\r\n",
        server->teams[i].channel[k].thread[j].thread_id,
        server->clients[id].user_id, "10:00",
        server->teams[i].channel[k].thread[j].thread_title,
        server->teams[i].channel[k].thread[j].thread_content);
}

void send_confirmation(server_t *server, int id, int i, int j)
{
    int k = 0;

    for (k = 0; strcmp(server->teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]); k++);
    delay(1);
    dprintf(server->clients[id].fd_client,
        "227 You succesfully created the thread \"%s\"\r\n",
        server->teams[i].channel[k].thread[j].thread_title);
    server->teams[i].channel[k].nb_thread++;
    server->teams[i].channel[k].thread[j].nb_comments = 0;
    server_event_thread_created(server->teams[i].channel[k].channel_id,
        server->teams[i].channel[k].thread[j].thread_id,
        server->clients[id].user_id,
        server->teams[i].channel[k].thread[j].thread_content);
}

void send_notif_thread(server_t *server, int id, int i, int j)
{
    int count = 0;
    int k = 0;

    call_client_lib(server, id, i, j);
    for (k = 0; strcmp(server->teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]); k++);
    delay(1);
    for (int a = 0; strcmp(server->teams[i].members[a].name, "NULL") != 0; a++)
        {
        for (count = 0; strcmp(server->clients[count].user_name,
            server->teams[i].members[a].name) != 0; count++);
        dprintf(server->clients[count].fd_client, "107|%s|%s|%s|%s|%s|\r\n",
        server->teams[i].channel[k].thread[j].thread_id,
        server->clients[id].user_id, "10:00",
        server->teams[i].channel[k].thread[j].thread_title,
        server->teams[i].channel[k].thread[j].thread_content);
    }
    send_confirmation(server, id, i, j);
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
    if (!thread_already_exist(server->teams[i].channel[k], name, server, id) ||
        !user_subscribed(server, i, id, "thread"))
        return;
    for (j = 0; strcmp(server->teams[i].channel[k].thread[j].thread_id,
        "NULL"); j++);
    server->teams[i].channel[k].thread = realloc(
        server->teams[i].channel[k].thread, sizeof(thread_t) * (j + 2));
    memset(&server->teams[i].channel[k].thread[j], 0, sizeof(thread_t));
    server->teams[i].channel[k].thread[j].comment = malloc(sizeof(char *));
    set_thread(&server->teams[i].channel[k].thread[j], name, desc);
    init_first_comment(server, i, k, j);
    send_notif_thread(server, id, i, j);
}
