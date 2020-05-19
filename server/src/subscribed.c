/*
** EPITECH PROJECT, 2020
** tools.c
** File description:
** tools.c
*/

#include "server.h"

void list_user_sub(server_t *server, char *team_id, int id, int client)
{
    int i = 0;

    (void)id;
    dprintf(client, "208 List of all user in this team\n");
    for (; strcmp(server->teams[i].team_id, "NULL"); i++) {
        if (!strcmp(server->teams[i].team_id, team_id))
            for (int k = 0; server->teams[i].members[k] != NULL; k++)
                dprintf(client, "%s.\n", server->teams[i].members[k]);
    }
}

void list_team_sub(server_t *server, int id, int client)
{
    int i = 0;
    int teams = 0;

    dprintf(client, "207 List of teams that you are in\n");
    for (i = 0; strcmp(server->teams[i].team_id, "NULL"); i++) {
        for (int k = 0; strcmp(server->teams[i].members[k], "NULL"); k++)
            if (!strcmp(server->teams[i].members[k],
                server->clients[id].user_name)) {
                dprintf(client, "Team name -> \"%s\"    Team ID -> \"%s\"\n",
                    server->teams[i].team_name,
                    server->teams[i].team_id);
                teams++;
            }
    }
    (teams == 0) ? dprintf(client, "you're not in any team.\n") : (0);
}

void subscribed(server_t *server, int client, int id)
{
    char *team_id = parse_args(server, 0);

    if (!server->clients[id].logged) {
        dprintf(client, "515 User not logged\r\n");
        dprintf(client, "128|\n");
    }
    else if (!strcmp(team_id, "Bad cmd") || strlen(team_id) < 1)
        list_team_sub(server, id, client);
    else
        list_user_sub(server, team_id, id, client);
}