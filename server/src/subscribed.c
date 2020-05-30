/*
** EPITECH PROJECT, 2020
** tools.c
** File description:
** tools.c
*/

#include "server.h"

void display_list(server_t *server, int client, int i, int k)
{
    dprintf(client, "208 List of all user in this team\r\n");
    for (; strcmp(server->teams[i].members[k].name, "NULL"); k++)
        dprintf(client, "User name : %s.\r\n",
            server->teams[i].members[k].name);
    (k == 0) ?
        dprintf(client, "0 users subscribed to this team\r\n") : 0;
}

void list_user_sub(server_t *server, char *team_id, int id, int client)
{
    int i = 0;
    int k = 0;

    (void)id;
    for (; strcmp(server->teams[i].team_id, "NULL"); i++)
        if (!strcmp(server->teams[i].team_id, team_id)) {
            display_list(server, client, i, k);
            return;
        }
    dprintf(client, "304 Team doesn't exist\r\n");
}

int display_members(server_t *server, int id, int i, int teams)
{
    for (int k = 0; strcmp(server->teams[i].members[k].name, "NULL"); k++)
        if (!strcmp(server->teams[i].members[k].name,
            server->clients[id].user_name)) {
            dprintf(server->clients[id].fd_client,
                "Team name -> \"%s\"    Team ID -> \"%s\"\r\n",
                server->teams[i].team_name,
                server->teams[i].team_id);
            teams++;
        }
    return (teams);
}

void list_team_sub(server_t *server, int id, int client)
{
    int i = 0;
    int teams = 0;

    dprintf(client, "207 List of teams that you are in\r\n");
    for (i = 0; strcmp(server->teams[i].team_id, "NULL"); i++) {
        for (int k = 0; strcmp(server->teams[i].members[k].name, "NULL"); k++)
            teams = display_members(server, id, i, teams);
    }
    (teams == 0) ? dprintf(client, "you're not in any team.\r\n") : (0);
}

void subscribed(server_t *server, int client, int id)
{
    char *team_id = parse_args(server, 0);

    if (!server->clients[id].logged) {
        dprintf(client, "515 User not logged\r\n");
        delay(1);
        dprintf(client, "128|\r\n");
        free(team_id);
        return;
    }
    if (count_args(server, 2))
        dprintf(client, "501 Error syntax in parameters or arguments\r\n");
    else if (!strcmp(team_id, "Bad cmd") || strlen(team_id) < 1)
        list_team_sub(server, id, client);
    else
        list_user_sub(server, team_id, id, client);
    free(team_id);
}
