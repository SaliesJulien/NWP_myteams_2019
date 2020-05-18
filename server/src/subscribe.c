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

    for (k = 0; strcmp(server->teams[k].team_id, "NULL"); k++)
        if (!strcmp(server->teams[k].team_id, team_id))
            break;
    for (; strcmp(server->teams[k].members[i], "NULL"); i++);
    server->teams[k].members = realloc(server->teams[k].members,
        sizeof(char *) * (i + 2));
    server->teams[k].members[i] = malloc(sizeof(char) *
        strlen(server->clients[id].user_name));
    server->teams[k].members[i + 1] = malloc(sizeof(char) * 4);
    strcpy(server->teams[k].members[i], server->clients[id].user_name);
    strcpy(server->teams[k].members[i + 1], "NULL");
    dprintf(client, "206 You succesfully subscribed to the team\n");
}

bool does_team_exist(server_t *server, char *team_id)
{
    for (int i = 0; strcmp(server->teams[i].team_id, "NULL"); i++) {
        if (!strcmp(server->teams[i].team_id, team_id))
            return (true);
    }
    return (false);
}

bool user_in_team(server_t *server, char *team_id, int id)
{
    int i = 0;
    int k = 0;

    for (i = 0; strcmp(server->teams[i].team_id, team_id); i++);
    for (k = 0; strcmp(server->teams[i].members[k], "NULL"); k++)
        if (!strcmp(server->teams[i].members[k],
            server->clients[id].user_name))
            return (true);
    return (false);
}

void subscribe(server_t *server, int client, int id)
{
    char *team_id = parse_args(server, 0);

    if (!strcmp(team_id, "Bad cmd") || strlen(team_id) < 1)
        dprintf(client, "501 Error syntax in parameters or arguments\n");
    else {
        if (!does_team_exist(server, team_id))
            dprintf(client, "304 Team doesn't exist\n");
        else if (user_in_team(server, team_id, id))
            dprintf(client, "You are already in this team.\n");
        else
            sub_team(server, client, team_id, id);
    }
}