/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

bool use_team(server_t *server, int client, int id, char *team)
{
    for (int i = 0; server->clients[id].teams[i].team_id != NULL; i++) {
        if (!strcmp(server->clients[id].teams[i].team_id, team)) {
            server->clients[server->nb_clients].use_state[0] = malloc(sizeof(char) * strlen(team));
            strcpy(server->clients[server->nb_clients].use_state[0], team);
            dprintf(client, "you entered in the \"%s\"",
                    server->clients[id].teams[i].team_name);
            return (true);
        }
    }
    return (false);
}

/*bool use_channel(server_t *server, int client, int id)
{
}

bool use_thread(server_t *server, int client, int id)
{
}*/

void use(server_t *server, int client, int id)
{
    char *team = parse_args(server, 0);
    //char *channel = parse_args(server, 2);
    //char *thread = parse_args(server, 4);

    if (team == NULL || strlen(team) <= 1)
        if (!use_team(server, client, id, team))
            dprintf(client, "Team unknow.\n");
}