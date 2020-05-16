/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

void init_next_team(server_t *server, int i)
{
    strcpy(server->teams[i].team_name, "NULL");
    strcpy(server->teams[i].team_desc, "NULL");
    strcpy(server->teams[i].team_id, "NULL");
}

void init_first_channel(server_t *server, int i)
{
    strcpy(server->teams[i].channel[0].channel_id, "NULL");
    strcpy(server->teams[i].channel[0].channel_name, "NULL");
    strcpy(server->teams[i].channel[0].channel_desc, "NULL");
}

bool team_already_exist(server_t *server, char *team_name, int id)
{
    for (int i = 0; strcmp(server->teams[i].team_id, "NULL"); i++)
        if (!strcmp(server->teams[i].team_name, team_name)) {
            dprintf(server->clients[id].fd_client,
                "This team name is already taken.\n");
            return (false);
        }
    return (true);
}

void create_new_team(server_t *server, int id, char *team_name,
    char *team_desc)
{
    int i = 0;

    if (!team_already_exist(server, team_name, id))
        return;
    for (; strcmp(server->teams[i].team_id, "NULL"); i++);
    server->teams = realloc(server->teams, sizeof(team_t) * (i + 2));
    server->teams[i].members = malloc(sizeof(char *) * 2);
    server->teams[i].members[0] = malloc(sizeof(char) *
        strlen(server->clients[id].user_name));
    server->teams[i].channel = malloc(sizeof(channel_t));
    strcpy(server->teams[i].team_id, generate_id());
    strcpy(server->teams[i].team_name, team_name);
    strcpy(server->teams[i].team_desc, team_desc);
    strcpy(server->teams[i].members[0], "NULL");
    init_first_channel(server, i);
    init_next_team(server, i + 1);
    dprintf(server->clients[id].fd_client, "New team \"%s\" created.\n",
            server->teams[i].team_id);
    server->nb_teams++;
}

void create(server_t *server, int client, int id)
{
    char *team_name = parse_args(server, 0);
    char *team_desc = parse_args(server, 2);

    if (!server->clients[id].use_state[2]) {
        if (count_args(server, 2)) {
            if (!strcmp(team_name, "Bad cmd") || !strcmp(team_desc, "Bad cmd"))
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
            dprintf(client, "501 Syntax error in parameters or arguments.\n");
    }
    else
        comment_error(server, team_name, id);
}
