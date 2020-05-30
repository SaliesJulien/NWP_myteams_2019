/*
** EPITECH PROJECT, 2020
** read.c
** File description:
** read.c
*/

#include "server.h"

server_t *read_teams(server_t *server, FILE *channel_teams, FILE *thread_teams,
    int i)
{
    if (channel_teams != NULL) {
        server->teams[i].channel = malloc((server->teams[i].nb_channel + 1) *
            sizeof(channel_t));
        fread(server->teams[i].channel, sizeof(channel_t),
            server->teams[i].nb_channel, channel_teams);
        strcpy(server->teams[i].channel[server->teams[i].nb_channel].channel_id
            , "NULL");
    }
    if (thread_teams != NULL) {
        for (int a = 0; a < server->teams[i].nb_channel; a++) {
            server->teams[i].channel[a].thread = malloc(
                (server->teams[i].channel[a].nb_thread + 1) *
                sizeof(thread_t));
            fread(server->teams[i].channel[a].thread, sizeof(thread_t),
                server->teams[i].channel[a].nb_thread, thread_teams);
            strcpy(server->teams[i].channel[a].thread[server->teams[i].
                channel[a].nb_thread].thread_id, "NULL");
        }
    }
    return (server);
}

server_t *read_members(server_t *server, FILE *members_teams, int i)
{
    if (members_teams != NULL) {
        server->teams[i].members = malloc((server->teams[i].nb_members + 1) *
            sizeof(members_t));
        fread(server->teams[i].members, sizeof(members_t),
            server->teams[i].nb_members, members_teams);
        strcpy(server->teams[i].members[server->teams[i].nb_members].name,
            "NULL");
        strcpy(server->teams[i].members[server->teams[i].nb_members].id,
            "NULL");
    }
    return (server);
}

void remove_client(server_t *server, int client, int id)
{
    if (strcmp(server->command, "/logout") == 0) {
        id = send_notification_logout(server, client, id);
        printf("Client disconnected\r\n");
        server_event_user_logged_out(server->clients[id].user_id);
    } else
        dprintf(client, "501 Error syntax in parameters or arguments\r\n");
}