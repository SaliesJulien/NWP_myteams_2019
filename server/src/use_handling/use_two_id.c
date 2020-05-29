/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

void use_channel_with_two_args(server_t *server, int id, char *chan, char *thread)
{
    int i = 0;
    int k = 0;
    bool thread_exist = false;
    bool channel_exist = false;

    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (; strcmp(server->teams[i].channel[k].channel_id, "NULL"); k++) {
        if (!strcmp(server->teams[i].channel[k].channel_id, chan)) {
            server->clients[id].use_state[1] =
                malloc(sizeof(char) * strlen(chan) + 1);
            strcpy(server->clients[id].use_state[1], chan);
            channel_exist = true;
            break;
        }
    }
    if (!channel_exist) {
        dprintf(server->clients[id].fd_client, "305 Channel doesn't exist\r\n");
        delay(1);
        dprintf(server->clients[id].fd_client, "115|%s|\r\n", chan);
    }
    for (int j = 0; strcmp(server->teams[i].channel[k].thread[j].thread_id, "NULL"); j++) {
        if (!strcmp(server->teams[i].channel[k].thread[j].thread_id, thread)) {
            server->clients[id].use_state[2] =
                malloc(sizeof(char) * strlen(thread) + 1);
            strcpy(server->clients[id].use_state[2], thread);
            thread_exist = true;
            break;
        }
    }
    if (!thread_exist) {
        dprintf(server->clients[id].fd_client, "306 Thread doesn't exist\r\n");
        delay(1);
        dprintf(server->clients[id].fd_client, "116|%s|\r\n", thread);
    }
}

void use_team_with_two_args(server_t *server, int id, char *team, char *chan)
{
    int i = 0;
    bool team_exist = false;
    bool channel_exist = false;

    (void)chan;
    for (; strcmp(server->teams[i].team_id, "NULL"); i++) {
        if (strcmp(server->teams[i].team_id, team) == 0) {
            server->clients[id].use_state[0] =
                malloc(sizeof(char) * strlen(team) + 1);
            strcpy(server->clients[id].use_state[0], team);
            team_exist = true;
            break;
        }
    }
    if (!team_exist) {
        dprintf(server->clients[id].fd_client, "304 Team doesn't exist\r\n");
        delay(1);
        dprintf(server->clients[id].fd_client, "114|%s|\r\n", team);
        return;
    }
    for (int k = 0; strcmp(server->teams[i].channel[k].channel_id, "NULL"); k++) {
        if (strcmp(server->teams[i].channel[k].channel_id, chan) == 0) {
            server->clients[id].use_state[1] =
                malloc(sizeof(char) * strlen(chan) + 1);
            strcpy(server->clients[id].use_state[1], chan);
            channel_exist = true;
            break;
        }
    }
    if (!channel_exist) {
        dprintf(server->clients[id].fd_client, "305 Channel doesn't exist\r\n");
        delay(1);
        dprintf(server->clients[id].fd_client, "115|%s|\r\n", chan);
        return;
    }
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
