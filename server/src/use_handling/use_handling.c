/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

bool use_team(server_t *server, int client, int id, char *team)
{
    (void)client;
    for (int i = 0; strcmp(server->teams[i].team_id, "NULL"); i++) {
        if (!strcmp(server->teams[i].team_id, team)) {
            server->clients[id].use_state[0] =
                malloc(sizeof(char) * strlen(team) + 1);
            strcpy(server->clients[id].use_state[0], team);
            return (true);
        }
    }
    return (false);
}

bool use_channel(server_t *server, int client, int id, char *channel)
{
    int i = 0;
    int k = 0;

    (void)client;
    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (k = 0; strcmp(server->teams[i].channel[k].channel_id, "NULL"); k++)
        if (!strcmp(server->teams[i].channel[k].channel_id, channel)) {
            server->clients[id].use_state[1] =
                malloc(sizeof(char) * strlen(channel) + 1);
            strcpy(server->clients[id].use_state[1], channel);
            return (true);
        }
    return (false);
}

bool use_thread(server_t *server, int client, int id, char *thread)
{
    int i = 0;
    int k = 0;
    int j = 0;

    (void)client;
    if (!strcmp(thread, server->clients[id].use_state[0])) {
        server->clients[id].use_state[1] = NULL;
        server->clients[id].use_state[0] =
                malloc(sizeof(char) * strlen(thread) + 1);
            strcpy(server->clients[id].use_state[0], thread);
    }
    else {
        for (i = 0; strcmp(server->teams[i].team_id,
            server->clients[id].use_state[0]); i++);
        for (k = 0; strcmp(server->teams[i].channel[k].channel_id,
            server->clients[id].use_state[1]); k++);
        for (; strcmp(server->teams[i].channel[k].thread[j].thread_id, "NULL");
            j++)
            if (strcmp(server->teams[i].channel[k].thread[j].thread_id, thread) == 0) {
                server->clients[id].use_state[2] =
                    malloc(sizeof(char) * strlen(thread) + 1);
                strcpy(server->clients[id].use_state[2], thread);
                return (true);
            }
        return (false);
    }
    return (true);
}

void use_backward(server_t *server, int client, int id, char *id_command)
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

void one_args(server_t *server, int client, int id)
{
    char *team = parse_args(server, 0);

    if (server->clients[id].use_state[2] != NULL)
        use_backward(server, client, id, team);
    else if (server->clients[id].use_state[1] != NULL &&
        server->clients[id].use_state[2] == NULL) {
        if (!use_thread(server, client, id, team)) {
            dprintf(client, "306 Thread doesn't exist\r\n");
            delay(1);
            dprintf(client, "116|%s|\r\n", team);
        }
    } else if (server->clients[id].use_state[0] != NULL &&
        server->clients[id].use_state[1] == NULL) {
        if (!use_channel(server, client, id, team)) {
            dprintf(client, "305 Channel doesn't exist\r\n");
            delay(1);
            dprintf(client, "115|%s|\r\n", team);
        }
    } else if (server->clients[id].use_state[0] == NULL)
        if (!use_team(server, client, id, team)) {
            dprintf(client, "304 Team doesn't exist\r\n");
            delay(1);
            dprintf(client, "114|%s|\r\n", team);
        }

    free(team);
}

void use(server_t *server, int client, int id)
{
    if (!server->clients[id].logged) {
        dprintf(client, "515 User not logged\r\n");
        delay(1);
        dprintf(client, "128|\r\n");
    } else if (count_args(server, 1))
        one_args(server, client, id);
    else if (count_args(server, 2))
        two_args(server, client, id);
    else if (count_args(server, 3))
        three_args(server, id, false, false);
    else if (count_args(server, 0))
        use_back(server, client, id);
    else
        dprintf(client, "501 Error syntax in parameters or arguments\r\n");
}
