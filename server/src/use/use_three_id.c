/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

void go_thread_with_three_args(channel_t *channel, clients_t *clients,
    server_t *server)
{
    char *thread = parse_args(server, 4);
    bool thread_exist = false;

    for (int j = 0; strcmp(channel->thread[j].thread_id, "NULL"); j++) {
        if (!strcmp(channel->thread[j].thread_id, thread)) {
            clients->use_state[2] =
                malloc(sizeof(char) * strlen(thread) + 1);
            strcpy(clients->use_state[2], thread);
            dprintf(clients->fd_client,
                "212 You are now in the thread \"%s\"\n",
                channel->thread[j].thread_title);
            thread_exist = true;
            break;
        }
    }
    if (!thread_exist)
        unknown_thread(clients, thread);
    free(thread);
}

void go_channel_with_three_args(team_t *teams, clients_t *clients,
    server_t *server, bool channel_exist)
{
    int k = 0;
    char *chan = parse_args(server, 2);

    for (; strcmp(teams->channel[k].channel_id, "NULL"); k++)
        if (strcmp(teams->channel[k].channel_id, chan) == 0) {
            clients->use_state[1] =
                malloc(sizeof(char) * strlen(chan) + 1);
            strcpy(clients->use_state[1], chan);
            dprintf(clients->fd_client,
                "211 You are now in the channel \"%s\"\n",
                teams->channel[k].channel_name);
            channel_exist = true;
            break;
        }
    if (!channel_exist) {
        unknown_channel(clients, chan);
        return;
    }
    go_thread_with_three_args(&teams->channel[k],
        clients, server);
    free(chan);
}

void three_args(server_t *server, int id, bool team_exist, bool channel_exist)
{
    char *team = parse_args(server, 0);
    int i = 0;

    for (; strcmp(server->teams[i].team_id, "NULL"); i++)
        if (strcmp(server->teams[i].team_id, team) == 0) {
            server->clients[id].use_state[0] =
                malloc(sizeof(char) * strlen(team) + 1);
            strcpy(server->clients[id].use_state[0], team);
            dprintf(server->clients[id].fd_client,
                "210 You are now in the team \"%s\"\n",
                server->teams[i].team_name);
            team_exist = true;
            break;
        }
    if (!team_exist) {
        unknown_team(server, team, id);
        return;
    }
    go_channel_with_three_args(&server->teams[i], &server->clients[id],
        server, channel_exist);
    free(team);
}