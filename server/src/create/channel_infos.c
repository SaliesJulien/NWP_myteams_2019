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