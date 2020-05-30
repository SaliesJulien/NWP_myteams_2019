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