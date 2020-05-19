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
        "209 You succesfully left this team\n");
    for (; strcmp(server->teams[i].members[k], "NULL"); k++)
        server->teams[i].members[k] = server->teams[i].members[k + 1];
    dprintf(server->clients[id].fd_client,
        "127|%s|%s|\n", server->clients[id].user_id,
        server->teams[i].team_id);
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

    if (!server->clients[id].logged) {
        dprintf(client, "515 User not logged\r\n");
        dprintf(client, "128|\n");
    }
    else if (!strcmp(team_id, "Bad cmd") || strlen(team_id) < 1)
        dprintf(client, "501 Error syntax in parameters or arguments\n");
    else {
        if (!team_exist(server, team_id)) {
            dprintf(client, "304 Team doesn't exist\n");
            dprintf(client, "114|%s|\n", team_id);
        }
        else if (!user_is_in_team(server, team_id, id))
            dprintf(client, "308 You aren't in this team\n");
        else
            leave_team(server, team_id, id);
    }
}
