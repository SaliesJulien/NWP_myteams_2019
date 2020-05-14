/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

void set_comment(thread_t *thread, int count, char *name, int client)
{
    thread->comment[count] = malloc(sizeof(char) * strlen(name));
    thread->comment[count + 1] = malloc(sizeof(char) * 5);
    strcpy(thread->comment[count], name);
    strcpy(thread->comment[count + 1], "NULL");
    dprintf(client, "New comment posted in thread -> %s.\n",
        thread->thread_title);
}

void create_new_comment(server_t *server, int id, char *name)
{
    int i = 0;
    int k = 0;
    int j = 0;
    int count = 0;

    for (; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (; strcmp(server->teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]); k++);
    for (; strcmp(server->teams[i].channel[k].thread[j].thread_id,
        server->clients[id].use_state[2]); j++);
    for (; strcmp(server->teams[i].channel[k].thread[j].comment[count], "NULL")
        ; count++);
    server->teams[i].channel[k].thread[j].comment =
        realloc(server->teams[i].channel[k].thread[j].comment,
        sizeof(char *) * (count + 2));
    set_comment(&server->teams[i].channel[k].thread[j],
        count, name, server->clients[id].fd_client);
}

void comment_error(server_t *server, char *team_name, char *team_desc, int id)
{
    if (!strcmp(team_name, "Bad cmd") || strlen(team_name) < 1)
        dprintf(server->clients[id].fd_client,
            "501 Syntax error in parameters or arguments.\n");
    else if ((!strcmp(team_desc, "Bad cmd") || strlen(team_desc) < 1) &&
        (strcmp(team_name, "Bad cmd") || strlen(team_name) > 1))
        create_new_comment(server, id, team_name);
    else
        dprintf(server->clients[id].fd_client,
            "501 Syntax error in parameters or arguments.\n");
}