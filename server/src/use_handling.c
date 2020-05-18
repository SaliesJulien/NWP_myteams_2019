/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

bool use_team(server_t *server, int client, int id, char *team)
{
    for (int i = 0; strcmp(server->teams[i].team_id, "NULL"); i++) {
        if (!strcmp(server->teams[i].team_id, team)) {
            server->clients[id].use_state[0] =
                malloc(sizeof(char) * strlen(team));
            server->clients[id].use_state[0] = team;
            dprintf(client, "210 You are now in the team \"%s\"\n",
                    server->teams[i].team_name);
            return (true);
        }
    }
    return (false);
}

bool use_channel(server_t *server, int client, int id, char *channel)
{
    int i = 0;
    int k = 0;

    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (k = 0; strcmp(server->teams[i].channel[k].channel_id, "NULL"); k++)
        if (!strcmp(server->teams[i].channel[k].channel_id, channel)) {
            server->clients[id].use_state[1] =
                malloc(sizeof(char) * strlen(channel));
            strcpy(server->clients[id].use_state[1], channel);
            dprintf(client, "211 You are now in the channel \"%s\"\n",
                    server->teams[i].channel[k].channel_name);
            return (true);
        }
    return (false);
}

bool use_thread(server_t *server, int client, int id, char *thread)
{
    int i = 0;
    int k = 0;
    int j = 0;

    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (k = 0; strcmp(server->teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]); k++);
    for (; strcmp(server->teams[i].channel[k].thread[j].thread_id, "NULL");
        j++)
        if (!strcmp(server->teams[i].channel[k].thread[j].thread_id, thread)) {
            server->clients[id].use_state[2] =
                malloc(sizeof(char) * strlen(thread));
            strcpy(server->clients[id].use_state[2], thread);
            dprintf(client, "212 You are now in the thread \"%s\"\n",
            server->teams[i].channel[k].thread[j].thread_title);
            return (true);
        }
    return (false);
}

void use(server_t *server, int client, int id)
{
    char *team = parse_args(server, 0);

    if (count_args(server, 1)) {
        if (strcmp(team, "Bad cmd")) {
            if (server->clients[id].use_state[1] &&
                !server->clients[id].use_state[2])
                if (!use_thread(server, client, id, team)) {
                    dprintf(client, "306 Thread doesn't exist\n");
                    dprintf(client, "116|%s|\n", team);
                }
            if (server->clients[id].use_state[0] &&
                !server->clients[id].use_state[1])
                if (!use_channel(server, client, id, team)) {
                    dprintf(client, "305 Channel doesn't exist\n");
                    dprintf(client, "115|%s|\n", team);
                }
            if (!server->clients[id].use_state[0])
                if (!use_team(server, client, id, team)) {
                    dprintf(client, "304 Team doesn't exist\n");
                    dprintf(client, "114|%s|\n", team);
                }
        }
        else
            dprintf(client, "501 Error syntax in parameters or arguments\n");
    }
    else
        use_back(server, client, id);
}