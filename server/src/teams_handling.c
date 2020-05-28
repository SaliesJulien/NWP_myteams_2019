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
                "510 This team already exist\r\n");
            dprintf(server->clients[id].fd_client,
                "129|\r\n");
            return (false);
        }
    return (true);
}

void create_new_team(server_t *server, int id, char *team_name,
    char *team_desc)
{
    int i = 0;
    char *id_generate = generate_id();

    if (!team_already_exist(server, team_name, id)) {
        free(id_generate);
        return;
    }
    for (; strcmp(server->teams[i].team_id, "NULL"); i++);
    server->teams = realloc(server->teams, sizeof(team_t) * (i + 2));
    memset(&server->teams[i], 0, sizeof(team_t));
    server->teams[i].members = malloc(sizeof(members_t));
    memset(server->teams[i].members, 0, sizeof(members_t));
    server->teams[i].channel = malloc(sizeof(channel_t));
    strcpy(server->teams[i].team_id, id_generate);
    free(id_generate);
    strcpy(server->teams[i].team_name, team_name);
    strcpy(server->teams[i].team_desc, team_desc);
    strcpy(server->teams[i].members[0].id, "NULL");
    strcpy(server->teams[i].members[0].name, "NULL");
    init_first_channel(server, i);
    init_next_team(server, i + 1);
    dprintf(server->clients[id].fd_client,
        "225 You succesfully created the team \"%s\"\r\n",
        server->teams[i].team_name);
    delay(1);
    dprintf(server->clients[id].fd_client,
        "122|%s|%s|%s|\r\n", server->teams[i].team_id,
        server->teams[i].team_name, server->teams[i].team_desc);
    delay(1);
    for (int a = 0; a < server->nb_clients; a++)
        dprintf(server->clients[a].fd_client,
            "105|%s|%s|%s|\r\n", server->teams[i].team_id,
            server->teams[i].team_name, server->teams[i].team_desc);
    server->nb_teams++;
    server->teams[i].nb_members = 0;
    server_event_team_created(server->teams[i].team_id, team_name,
        server->clients[id].user_id);
}

void create_statement(server_t *server, int id, char *team_name,
    char *team_desc)
{
    if (count_args(server, 2)) {
        if (!strcmp(team_name, "Bad cmd") || !strcmp(team_desc, "Bad cmd"))
            dprintf(server->clients[id].fd_client,
                "501 Syntax error in parameters or arguments.\r\n");
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
        dprintf(server->clients[id].fd_client,
            "501 Syntax error in parameters or arguments.\r\n");
}

void create(server_t *server, int client, int id)
{
    char *team_name = parse_args(server, 0);
    char *team_desc = parse_args(server, 2);

    if (server->clients[id].logged) {
        if (!server->clients[id].use_state[2])
            create_statement(server, id, team_name, team_desc);
        else
            comment_error(server, team_name, id);
    }
    else {
        dprintf(client, "515 User not logged\r\n");
    }
    free(team_name);
    free(team_desc);
}