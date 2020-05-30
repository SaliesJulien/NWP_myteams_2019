/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** login
*/

#include "server.h"

void list_clients_logged(server_t *server, int client, int id)
{
    (void)id;
    dprintf(client, "List of users logged in on the server\r\n");
    delay(1);
    for (int i = 0; i <= server->nb_clients; i++) {
        if (server->clients[i].active) {
            dprintf(client, "Username : \"%s\"    User ID : \"%s\"\r\n",
            server->clients[i].user_name, server->clients[i].user_id);
            delay(1);
            dprintf(client, "118|%s|%s|%d|\n", server->clients[i].user_id,
            server->clients[i].user_name, (server->clients[i].logged) ? 1 : 0);
        }
    }
}

void list_team_info(server_t *server, int client, int id)
{
    int i = 0;

    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    dprintf(client, "242 Team \"%s\" infos :\r\n", server->teams[i].team_name);
    delay(1);
    dprintf(client, "119|%s|%s|%s|\r\n", server->teams[i].team_id,
        server->teams[i].team_name, server->teams[i].team_desc);
    delay(1);
    dprintf(client, "Team name : \"%s\"    Team description : \"%s\"\r\n",
        server->teams[i].team_name,
        server->teams[i].team_desc);
}

void list_channel_info(server_t *server, int client, int id)
{
    int i = 0;
    int k = 0;

    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]) != 0; i++);
    for (k = 0; strcmp(server->teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]) != 0; k++);
    dprintf(client, "243 Channel \"%s\" infos :\r\n",
        server->teams[i].channel[k].channel_name);
    delay(1);
    dprintf(client, "120|%s|%s|%s|\r\n", server->teams[i].channel[k].channel_id
        , server->teams[i].channel[k].channel_name,
        server->teams[i].channel[k].channel_desc);
    delay(1);
    dprintf(client, "Channel name : \"%s\"    Channel description : \"%s\"\r\n"
        , server->teams[i].channel[k].channel_name,
        server->teams[i].channel[k].channel_desc);
}

void list_thread_info(server_t *server, int client, int id)
{
    int i = 0;
    int k = 0;
    int j = 0;

    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]); i++);
    for (k = 0; strcmp(server->teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]); k++);
    for (; strcmp(server->teams[i].channel[k].thread[j].thread_id,
        server->clients[id].use_state[2]); j++);
    dprintf(client, "121|%s|%s|%s|%s|%s|\r\n",
        server->teams[i].channel[k].thread[j].thread_id,
        server->clients[id].user_id, "10:00",
        server->teams[i].channel[k].thread[j].thread_title,
        server->teams[i].channel[k].thread[j].thread_content);
    delay(1);
    dprintf(client, "Thread title : \"%s\"    Thread description : \"%s\"\r\n",
        server->teams[i].channel[k].thread[j].thread_title,
        server->teams[i].channel[k].thread[j].thread_content);
}

void info(server_t *server, int client, int id)
{
    if (strcmp(server->command, "/info") == 0) {
        if (!server->clients[id].logged) {
            dprintf(client, "515 User not logged\r\n");
            delay(1);
            dprintf(client, "128|\r\n");
            return;
        }
        else if (!count_args(server, 0))
            dprintf(client, "501 Error syntax in parameters or arguments\r\n");
        (server->clients[id].use_state[2]) ?
            list_thread_info(server, client, id) : (0);
        (server->clients[id].use_state[1] && !server->clients[id].use_state[2])
            ? list_channel_info(server, client, id): (0);
        (server->clients[id].use_state[0] && !server->clients[id].use_state[1])
            ? list_team_info(server, client, id): (0);
        (!server->clients[id].use_state[0]) ?
            list_clients_logged(server, client, id) : (0);
    } else {
        dprintf(client, "501 Error syntax in parameters or arguments\r\n");
    }
}
