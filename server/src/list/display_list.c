/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** login
*/

#include "server.h"

void display_list_thread(server_t *server, int client, int id, int j)
{
    int i = 0;
    int k = 0;

    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]) != 0; i++);
    for (k = 0; strcmp(server->teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]) != 0; k++);
    dprintf(client, "Thread title -> \"%s\"    Thread ID -> \"%s\"\r\n",
        server->teams[i].channel[k].thread[j].thread_title,
        server->teams[i].channel[k].thread[j].thread_id);
    delay(1);
    dprintf(client, "111|%s|%s|10:20|%s|%s|\r\n",
        server->teams[i].channel[k].thread[j].thread_id,
        server->clients[id].user_id,
        server->teams[i].channel[k].thread[j].thread_title,
        server->teams[i].channel[k].thread[j].thread_content);
}

void display_list_replies(server_t *server, int client, int id, int c)
{
    int i = 0;
    int k = 0;
    int j = 0;

    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]) != 0; i++);
    for (k = 0; strcmp(server->teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]) != 0; k++);
    for (; strcmp(server->teams[i].channel[k].thread[j].thread_id,
        server->clients[id].use_state[2]) != 0; j++);
    dprintf(client, "Reply -> \"%s\"\r\n",
        server->teams[i].channel[k].thread[j].comment[c]);
    delay(1);
    dprintf(client, "112|%s|%s|10:20|%s\r\n",
        server->teams[i].channel[k].thread[j].thread_id,
        server->clients[id].user_id,
        server->teams[i].channel[k].thread[j].comment[c]);
}