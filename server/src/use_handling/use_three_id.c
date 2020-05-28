/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

void three_args(server_t *server, int id, bool team_exist, bool channel_exist)
{
    char *team = parse_args(server, 0);
    char *chan = parse_args(server, 2);
    char *thread = parse_args(server, 4);
    bool thread_exist = false;
    int i = 0;
    int k = 0;

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
    for (; strcmp(server->teams[i].channel[k].channel_id, "NULL"); k++) {
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
    free(team);
    free(chan);
    free(thread);
}