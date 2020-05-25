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

bool thread_already_exist(channel_t channel, char *name, server_t *server,
    int id)
{
    int j = 0;

    for (j = 0; strcmp(channel.thread[j].thread_id,
        "NULL"); j++)
        if (!strcmp(channel.thread[j].thread_title, name)) {
            dprintf(server->clients[id].fd_client,
                "512 This thread already exist\r\n");
            dprintf(server->clients[id].fd_client, "129|\r\n");
            return (false);
        }
    return (true);
}

void set_thread(thread_t *thread, char *name, char *desc)
{
    strcpy(thread->thread_id, generate_id());
    strcpy(thread->thread_title, name);
    strcpy(thread->thread_content, desc);
}

void create_new_thread(server_t *server, int id, char *name, char *desc)
{
    int i = 0;
    int k = 0;
    int j = 0;
    int count = 0;

    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (k = 0; strcmp(server->teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]); k++);
    if (!thread_already_exist(server->teams[i].channel[k], name, server, id))
        return;
    for (j = 0; strcmp(server->teams[i].channel[k].thread[j].thread_id,
        "NULL"); j++);
    server->teams[i].channel[k].thread = realloc(
        server->teams[i].channel[k].thread, sizeof(thread_t) * (j + 2));
    memset(&server->teams[i].channel[k].thread[j], 0, sizeof(thread_t));
    server->teams[i].channel[k].thread[j].comment = malloc(sizeof(char *));
    set_thread(&server->teams[i].channel[k].thread[j], name, desc);
    init_first_comment(server, i, k, j);
    dprintf(server->clients[id].fd_client,
        "124|%s|%s|%s|%s|%s|\r\n",
        server->teams[i].channel[k].thread[j].thread_id,
        server->clients[id].user_id, "10:00",
        server->teams[i].channel[k].thread[j].thread_title,
        server->teams[i].channel[k].thread[j].thread_content);
    for (int a = 0; strcmp(server->teams[i].members[a].name, "NULL") != 0; a++) {
        for (count = 0; strcmp(server->clients[count].user_name,
            server->teams[i].members[a].name) != 0; count++);
        dprintf(server->clients[count].fd_client, "107|%s|%s|%s|%s|%s|\r\n",
        server->teams[i].channel[k].thread[j].thread_id,
        server->clients[id].user_id, "10:00",
        server->teams[i].channel[k].thread[j].thread_title,
        server->teams[i].channel[k].thread[j].thread_content);
    }
    dprintf(server->clients[id].fd_client,
        "227 You succesfully created the thread \"%s\"\r\n",
        server->teams[i].channel[k].thread[j].thread_title);
    init_next_thread(server, i, k, j + 1);
    server->teams[i].channel[k].nb_thread++;
    server_event_thread_created(server->teams[i].channel[k].channel_id,
        server->teams[i].channel[k].thread[j].thread_id,
        server->clients[id].user_id,
        server->teams[i].channel[k].thread[j].thread_content);
}
