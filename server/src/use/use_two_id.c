/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

void good_chan_now_thread(channel_t *channel, char *thread, clients_t *clients)
{
    bool thread_exist = false;

    for (int j = 0; strcmp(channel->thread[j].thread_id,
        "NULL"); j++) {
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
}

void use_channel_with_two_args(server_t *server, int id, char *chan,
    char *thread)
{
    int i = 0;
    int k = 0;
    bool channel_exist = false;

    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (; strcmp(server->teams[i].channel[k].channel_id, "NULL"); k++)
        if (!strcmp(server->teams[i].channel[k].channel_id, chan)) {
            server->clients[id].use_state[1] =
                malloc(sizeof(char) * strlen(chan) + 1);
            strcpy(server->clients[id].use_state[1], chan);
            dprintf(server->clients[id].fd_client,
                "211 You are now in the channel \"%s\"\n",
                server->teams[i].channel[k].channel_name);
            channel_exist = true;
            break;
        }
    if (!channel_exist)
        unknown_channel(&server->clients[id], chan);
    good_chan_now_thread(&server->teams[i].channel[k], thread,
        &server->clients[id]);
}

void good_team_now_chan(team_t *teams, char *chan, clients_t *clients)
{
    bool channel_exist = false;

    for (int k = 0; strcmp(teams->channel[k].channel_id, "NULL"); k++)
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
        dprintf(clients->fd_client, "305 Channel doesn't exist\r\n");
        delay(1);
        dprintf(clients->fd_client, "115|%s|\r\n", chan);
        return;
    }
}

void use_team_with_two_args(server_t *server, int id, char *team, char *chan)
{
    int i = 0;
    bool team_exist = false;

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
    good_team_now_chan(&server->teams[i], chan,
        &server->clients[id]);
}

void two_args(server_t *server, int client, int id)
{
    char *team = parse_args(server, 0);
    char *chan = parse_args(server, 2);

    (void)client;
    if (server->clients[id].use_state[0] != NULL &&
        server->clients[id].use_state[1] == NULL)
        use_channel_with_two_args(server, id, team, chan);
    else if (server->clients[id].use_state[0] == NULL)
        use_team_with_two_args(server, id, team, chan);
    free(team);
    free(chan);
}
