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

void print_team(server_t *server, int id, int client)
{
    for (int i = 0; server->clients[id].teams[i].team_id != NULL; i++) {
        dprintf(client, "%s\n", server->clients[id].teams[i].team_name);
        dprintf(client, "%s\n", server->clients[id].teams[i].team_desc);
        dprintf(client, "%s\n", server->clients[id].teams[i].team_id);
    }
}

void create_new_team(server_t *server, int id, char *team_name, char *team_desc)
{
    int i = 0;

    for (i = 0; server->clients[id].teams[i].team_id != NULL; i++);
    server->clients[id].teams = realloc(server->clients[id].teams, sizeof(team_t) * (i + 2));
    server->clients[id].teams[i].team_name = malloc(sizeof(char) * strlen(team_name));
    server->clients[id].teams[i].team_desc = malloc(sizeof(char) * strlen(team_desc));
    server->clients[id].teams[i].team_id = malloc(sizeof(char) * 37);
    server->clients[id].teams[i].channel = malloc(sizeof(channel_t));
    strcpy(server->clients[id].teams[i].team_name, team_name);
    strcpy(server->clients[id].teams[i].team_desc, team_desc);
    strcpy(server->clients[id].teams[i].team_id, generate_id());
    init_next_team(server, id, i + 1);
}

void create_new_channel(server_t *server, int id)
{
    int i = 0;

    for (i = 0; server->clients[id].teams[i].team_id !=
                server->clients[id].use_state[0]; i++);
    server->clients[id].teams[i].channel =
        realloc(server->clients[id].teams[i].channel, sizeof(channel_t) * (i + 2));
}

void create(server_t *server, int client, int id)
{
    char *team_name = parse_args(server, 0);
    char *team_desc = parse_args(server, 2);

    if (strcmp(team_desc, "Bad cmd") == 0 || strcmp(team_name, "Bad cmd") == 0)
        dprintf(client, "501 Syntax error in parameters or arguments.\n");
    if (server->clients[id].use_state[0] == NULL)
        create_new_team(server, id, team_name, team_desc);
    if (server->clients[id].use_state[0] != NULL)
        create_new_channel(server, id);
}