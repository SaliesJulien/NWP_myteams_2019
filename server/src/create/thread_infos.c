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

void set_thread(thread_t *thread, char *name, char *desc)
{
    char *id = generate_id();

    strcpy(thread->thread_id, id);
    strcpy(thread->thread_title, name);
    strcpy(thread->thread_content, desc);
    free(id);
}