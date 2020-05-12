/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

void init_next_team(server_t *server, int id, int i)
{
    strcpy(server->clients[id].teams[i].team_name, "NULL");
    strcpy(server->clients[id].teams[i].team_desc, "NULL");
    strcpy(server->clients[id].teams[i].team_id, "NULL");

}

void create_new_team(server_t *server, int id, char *team_name,
    char *team_desc)
{
    int i = 0;

    for (i = 0; strcmp(server->clients[id].teams[i].team_id, "NULL") != 0; i++);
    server->clients[id].teams =
        realloc(server->clients[id].teams, sizeof(team_t) * (i + 2));
    server->clients[id].teams[i].channel = malloc(sizeof(channel_t));
    init_next_channel(server, id, i, 0);
    strcpy(server->clients[id].teams[i].team_name, team_name);
    strcpy(server->clients[id].teams[i].team_desc, team_desc);
    strcpy(server->clients[id].teams[i].team_id, generate_id());
    dprintf(server->clients[id].fd_client, "New team \"%s\" created.\n",
            server->clients[id].teams[i].team_id);
    init_next_team(server, id, i + 1);
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
    else
        comment_error(server, team_name, team_desc, id);
}