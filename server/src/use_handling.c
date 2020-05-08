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
            server->clients[id].use_state[0] =
                malloc(sizeof(char) * strlen(team));
            server->clients[id].use_state[0] = team;
            dprintf(client, "you entered in team -> \"%s\"\n",
                    server->clients[id].teams[i].team_name);
            return (true);
        }
    }
    return (false);
}

bool use_channel(server_t *server, int client, int id, char *channel)
{
    int i = 0;

    for (i = 0; strcmp(server->clients[id].teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (int k = 0; server->clients[id].teams[i].channel[k].channel_id
        != NULL; k++)
        if (!strcmp(server->clients[id].teams[i].channel[k].channel_id,
                channel)) {
            server->clients[id].use_state[1] =
                malloc(sizeof(char) * strlen(channel));
            strcpy(server->clients[id].use_state[1], channel);
            dprintf(client, "you entered in channel -> \"%s\"\n",
                    server->clients[id].teams[i].channel[k].channel_name);
            return (true);
        }
    return (false);
}

bool use_thread(server_t *server, int client, int id, char *thread)
{
    int i = 0;
    int k = 0;
    int j = 0;

    for (i = 0; strcmp(server->clients[id].teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (k = 0; strcmp(server->clients[id].teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]); k++);
    for (; server->clients[id].teams[i].channel[k].thread[j].thread_id; j++)
        if (!strcmp(
                server->clients[id].teams[i].channel[k].thread[j].thread_id,
                thread)) {
            server->clients[id].use_state[2] =
                malloc(sizeof(char) * strlen(thread));
            strcpy(server->clients[id].use_state[2], thread);
            dprintf(client, "you entered in thread -> \"%s\"\n",
            server->clients[id].teams[i].channel[k].thread[j].thread_title);
            return (true);
        }
    return (false);
}

void use(server_t *server, int client, int id)
{
    char *team = parse_args(server, 0);

    if (team != NULL || strlen(team) > 0) {
        if (server->clients[id].use_state[1] &&
            !server->clients[id].use_state[2])
            if (!use_thread(server, client, id, team))
                dprintf(client, "Thread unknow.\n");
        if (server->clients[id].use_state[0] &&
            !server->clients[id].use_state[1])
            if (!use_channel(server, client, id, team))
                dprintf(client, "Channel unknow.\n");
        if (!server->clients[id].use_state[0])
            if (!use_team(server, client, id, team))
                dprintf(client, "Team unknow.\n");
    }
    else
        dprintf(client, "501 Syntax error in parameters or arguments.\n");
}