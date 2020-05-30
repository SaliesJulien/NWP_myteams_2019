/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

void init_next_team(server_t *server, int i)
{
    strcpy(server->teams[i].team_name, "NULL");
    strcpy(server->teams[i].team_desc, "NULL");
    strcpy(server->teams[i].team_id, "NULL");
}

void init_first_channel(server_t *server, int i)
{
    strcpy(server->teams[i].channel[0].channel_id, "NULL");
    strcpy(server->teams[i].channel[0].channel_name, "NULL");
    strcpy(server->teams[i].channel[0].channel_desc, "NULL");
}