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
    int k = 0;

    for (i = 0; strcmp(server->teams[i].team_id, team_id); i++);
    for (k = 0; strcmp(server->teams[i].members[k],
        server->clients[id].user_name); k++);
    dprintf(server->clients[id].fd_client,
        "You succesfully left the team \"%s\".\n",
        server->teams[i].team_name);
    for (; strcmp(server->teams[i].members[k], "NULL"); k++)
        server->teams[i].members[k] = server->teams[i].members[k + 1];
    strcpy(server->teams[i].members[k + 1], "NULL");
    server_event_user_leave_a_team(server->teams[i].team_id,
        server->clients[id].user_id);
}

bool team_exist(server_t *server, char *team_id)
{
    for (int i = 0; strcmp(server->teams[i].team_id, "NULL"); i++)
        if (!strcmp(server->teams[i].team_id, team_id))
            return (true);
    return (false);
}

bool user_is_in_team(server_t *server, char *team_id, int id)
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

void unsubscribe(server_t *server, int client, int id)
{
    char *team_id = parse_args(server, 0);

    if (!strcmp(team_id, "Bad cmd") || strlen(team_id) < 1)
        dprintf(client, "501 Syntax error in parameters or arguments.\n");
    else {
        if (!team_exist(server, team_id))
            dprintf(client, "This team doesn't exist.\n");
        else if (!user_is_in_team(server, team_id, id))
            dprintf(client, "You are not in this team.\n");
        else
            leave_team(server, team_id, id);
    }
}