/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

void init_next_team(server_t *server, int id, int i)
{
    server->clients[id].teams[i].team_name = NULL;
    server->clients[id].teams[i].team_desc = NULL;
    server->clients[id].teams[i].team_id = NULL;
}

void create_new_team(server_t *server, int id, char *team_name,
    char *team_desc)
{
    int i = 0;

    for (i = 0; server->clients[id].teams[i].team_id != NULL; i++);
    server->clients[id].teams =
        realloc(server->clients[id].teams, sizeof(team_t) * (i + 2));
    server->clients[id].teams[i].team_name =
        malloc(sizeof(char) * strlen(team_name));
    server->clients[id].teams[i].team_desc =
        malloc(sizeof(char) * strlen(team_desc));
    server->clients[id].teams[i].team_id = malloc(sizeof(char) * 37);
    server->clients[id].teams[i].channel = malloc(sizeof(channel_t));
    init_next_channel(server, id, i, 0);
    strcpy(server->clients[id].teams[i].team_name, team_name);
    strcpy(server->clients[id].teams[i].team_desc, team_desc);
    strcpy(server->clients[id].teams[i].team_id, generate_id());
    dprintf(server->clients[id].fd_client, "New team \"%s\" created.\n",
            server->clients[id].teams[i].team_id);
    init_next_team(server, id, i + 1);
}

void set_comment(thread_t *thread, int count, char *name, int client)
{
    thread->comment[count] = malloc(sizeof(char) * strlen(name));
    strcpy(thread->comment[count], name);
    dprintf(client, "New comment posted in thread -> %s.\n",
        thread->thread_title);
    thread->comment[count++] = NULL;
}

void create_new_comment(server_t *server, int id, char *name)
{
    int i = 0;
    int k = 0;
    int j = 0;
    int count = 0;

    for (; strcmp(server->clients[id].teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (; strcmp(server->clients[id].teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]); k++);
    for (; strcmp(server->clients[id].teams[i].channel[k].thread[j].thread_id,
        server->clients[id].use_state[2]); j++);
    for (; server->clients[id].teams[i].channel[k].thread[j].comment[count]
        != NULL; count++);
    server->clients[id].teams[i].channel[k].thread[j].comment =
        realloc(server->clients[id].teams[i].channel[k].thread[j].comment,
        sizeof(char *) * (count + 2));
    set_comment(&server->clients[id].teams[i].channel[k].thread[j],
        count, name, server->clients[id].fd_client);
}

void create(server_t *server, int client, int id)
{
    char *team_name = parse_args(server, 0);
    char *team_desc = parse_args(server, 2);

    if (!server->clients[id].use_state[2]) {
        if ((team_desc == NULL || strlen(team_desc) < 1) ||
            (team_name == NULL || strlen(team_name) < 1))
            dprintf(client, "501 Syntax error in parameters or arguments.\n");
        else if (server->clients[id].use_state[0] == NULL)
            create_new_team(server, id, team_name, team_desc);
        else if (server->clients[id].use_state[0] &&
            !server->clients[id].use_state[1])
            create_new_channel(server, id, team_name, team_desc);
        else if (server->clients[id].use_state[1] &&
            !server->clients[id].use_state[2])
            create_new_thread(server, id, team_name, team_desc);
    }
    else {
        (team_name == NULL || strlen(team_name) < 1) ?
            dprintf(client, "501 Syntax error in parameters or arguments.\n") :
            create_new_comment(server, id, team_name);
    }
}