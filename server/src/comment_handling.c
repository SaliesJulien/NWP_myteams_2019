/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

int team_nb(server_t *server, int id)
{
    int i = 0;

    for (; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    return (i);
}

int channel_nb(server_t *server, int id, int i)
{
    int k = 0;

    for (; strcmp(server->teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]); k++);
    return (k);
}

int thread_nb(server_t *server, int id, int i, int k)
{
    int j = 0;

    for (; strcmp(server->teams[i].channel[k].thread[j].thread_id,
        server->clients[id].use_state[2]); j++);
    return (j);
}

int comment_nb(server_t *server, int i, int k, int j)
{
    int count = 0;

    for (; strcmp(server->teams[i].channel[k].thread[j].comment[count], "NULL")
        ; count++);
    return (count);
}

void create_new_comment(server_t *server, int id, char *name)
{
    int i = team_nb(server, id);
    int k = channel_nb(server, id, i);
    int j = thread_nb(server, id, i, k);
    int count = comment_nb(server, i, k, j);

    server->teams[i].channel[k].thread[j].comment =
        realloc(server->teams[i].channel[k].thread[j].comment,
        sizeof(char *) * (count + 2));
    server->teams[i].channel[k].thread[j].comment[count] =
        malloc(sizeof(char) * strlen(name));
    server->teams[i].channel[k].thread[j].comment[count + 1] =
        malloc(sizeof(char) * 5);
    strcpy(server->teams[i].channel[k].thread[j].comment[count], name);
    strcpy(server->teams[i].channel[k].thread[j].comment[count + 1], "NULL");
    dprintf(server->clients[id].fd_client,
        "New comment posted in thread -> %s.\n",
        server->teams[i].channel[k].thread[j].thread_title);
    fprintf(server->comments, "%s|%s|%s|%s|\n", server->teams[i].team_id,
        server->teams[i].channel[k].channel_id,
        server->teams[i].channel[k].thread[j].thread_id, name);
}

void comment_error(server_t *server, char *team_name, int id)
{
    if (count_args(server, 1))
        if (strcmp(team_name, "Bad cmd"))
            create_new_comment(server, id, team_name);
        else
            dprintf(server->clients[id].fd_client,
                "501 Syntax error in parameters or arguments.\n");
    else
        dprintf(server->clients[id].fd_client,
            "501 Syntax error in parameters or arguments.\n");
}
