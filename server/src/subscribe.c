/*
** EPITECH PROJECT, 2020
** tools.c
** File description:
** tools.c
*/

#include "server.h"

void sub_team(server_t *server, int client, char *team_id, int id)
{
    int i = 0;
    int k = 0;

    for (k = 0; server->teams[k].team_id != NULL; k++)
        if (!strcmp(server->teams[k].team_id, team_id))
            break;
    for (;server->teams[k].members[i] != NULL; i++);
    server->teams[k].members = realloc(server->teams[k].members,
        sizeof(char *) * (i + 2));
    server->teams[k].members[i] = malloc(sizeof(char) *
        strlen(server->clients[id].user_name));
    strcpy(server->teams[k].members[i], server->clients[id].user_name);
    server->teams[k].members[i + 1] = NULL;
    dprintf(client, "You joinded \"%s\".\n", server->teams[k].team_name);
}

bool does_team_exist(server_t *server, char *team_id)
{
    for (int i = 0; server->teams[i].team_id != NULL; i++) {
        if (!strcmp(server->teams[i].team_id, team_id))
            return (true);
    }
    return (false);
}

void subscribe(server_t *server, int client, int id)
{
    char *team_id = parse_args(server, 0);

    if (!strcmp(team_id, "Bad cmd") || strlen(team_id) < 1)
        dprintf(client, "501 Syntax error in parameters or arguments.\n");
    else {
        if (!does_team_exist(server, team_id))
            dprintf(client, "Team's Unknown.\n");
        else
            sub_team(server, client, team_id, id);
    }
}