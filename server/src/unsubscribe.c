/*
** EPITECH PROJECT, 2020
** tools.c
** File description:
** tools.c
*/

#include "server.h"

void leave_team(server_t *server, char *team_id, int id)
{
    int i = 0;

    for (i = 0; server->clients[id].teams[i].team_id; i++)
        if (!strcmp(server->clients[id].teams[i].team_id, team_id))
            break;
    dprintf(server->clients[id].fd_client,
        "You succesfully left the team \"%s\".\n",
        server->clients[id].teams[i].team_name);
    for (; server->clients[id].teams[i].team_id; i++)
        server->clients[id].teams[i] = server->clients[id].teams[i + 1];
    init_next_team(server, id, i);
}

bool team_exist(server_t *server, char *team_id, int id)
{
    for (int i = 0; server->clients[id].teams[i].team_id; i++)
        if (!strcmp(server->clients[id].teams[i].team_id, team_id))
            return (true);
    return (false);
}

void unsubscribe(server_t *server, int client, int id)
{
    char *team_id = parse_args(server, 0);

    if (!strcmp(team_id, "Bad cmd") || strlen(team_id) < 1)
        dprintf(client, "501 Syntax error in parameters or arguments.\n");
    else {
        if (!team_exist(server, team_id, id))
            dprintf(client, "You don't are in this team.\n");
        else
            leave_team(server, team_id, id);
    }
}