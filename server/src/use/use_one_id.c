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
                malloc(sizeof(char) * strlen(team) + 1);
            strcpy(server->clients[id].use_state[0], team);
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
                malloc(sizeof(char) * strlen(channel) + 1);
            strcpy(server->clients[id].use_state[1], channel);
            dprintf(client, "211 You are now in the channel \"%s\"\n",
                server->teams[i].channel[k].channel_name);
            return (true);
        }
    return (false);
}

bool go_in_thread(server_t *server, int id, char *thread)
{
    int i = 0;
    int k = 0;

    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (k = 0; strcmp(server->teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]); k++);
    for (int j = 0; strcmp(server->teams[i].channel[k].thread[j].thread_id,
        "NULL");
        j++)
        if (strcmp(server->teams[i].channel[k].thread[j].thread_id, thread)
            == 0) {
            server->clients[id].use_state[2] =
                malloc(sizeof(char) * strlen(thread) + 1);
            strcpy(server->clients[id].use_state[2], thread);
            dprintf(server->clients[id].fd_client,
                "212 You are now in the thread \"%s\"\n",
                server->teams[i].channel[k].thread[j].thread_title);
            return (true);
        }
    return (false);
}

bool use_thread(server_t *server, int client, int id, char *thread)
{
    int i = 0;

    if (!strcmp(thread, server->clients[id].use_state[0])) {
        server->clients[id].use_state[1] = NULL;
        server->clients[id].use_state[0] =
                malloc(sizeof(char) * strlen(thread) + 1);
            strcpy(server->clients[id].use_state[0], thread);
            for (; strcmp(server->teams[i].team_id, thread); i++);
            dprintf(client, "210 You are now in the team \"%s\"\n",
                server->teams[i].team_name);
    }
    else
        if (!go_in_thread(server, id, thread))
            return (false);
    return (true);
}

void use_in_thread(server_t *server, int client, int id, char *id_command)
{
    (void)client;
    if (!strcmp(id_command, server->clients[id].use_state[0])) {
        server->clients[id].use_state[2] = NULL;
        server->clients[id].use_state[1] = NULL;
        server->clients[id].use_state[0] =
                malloc(sizeof(char) * strlen(id_command) + 1);
            strcpy(server->clients[id].use_state[0], id_command);
    } else if (!strcmp(id_command, server->clients[id].use_state[1])) {
        server->clients[id].use_state[2] = NULL;
        server->clients[id].use_state[1] =
                malloc(sizeof(char) * strlen(id_command) + 1);
            strcpy(server->clients[id].use_state[1], id_command);
    }
}