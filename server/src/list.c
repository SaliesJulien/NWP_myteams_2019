/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** login
*/

#include "server.h"

void list_teams(server_t *server, int client)
{
    int i = 0;

    dprintf(client, "231 List of teams that exist on the server\r\n");
    delay(1);
    for (i = 0; strcmp(server->teams[i].team_id, "NULL") != 0; i++) {
        dprintf(client, "Team name -> \"%s\"    Team ID -> \"%s\"\r\n",
            server->teams[i].team_name,
            server->teams[i].team_id);
        delay(1);
        dprintf(client, "109|%s|%s|%s\r\n",
            server->teams[i].team_id,
            server->teams[i].team_name,
            server->teams[i].team_desc);
    }
    (i == 0) ? dprintf(client, "There is no any team.\r\n") : (0);
}

void list_channel(server_t *server, int client, int id)
{
    int i = 0;
    int k = 0;

    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]) != 0; i++);
    dprintf(client, "232 List of channels that exist on this team\r\n");
    delay(1);
    for (k = 0; strcmp(server->teams[i].channel[k].channel_id, "NULL") != 0; k++) {
        dprintf(client, "Channel name -> \"%s\"    Channel ID -> \"%s\"\r\n",
            server->teams[i].channel[k].channel_name,
            server->teams[i].channel[k].channel_id);
        delay(1);
        dprintf(client, "110|%s|%s|%s\r\n",
            server->teams[i].channel[k].channel_id,
            server->teams[i].channel[k].channel_name,
            server->teams[i].channel[k].channel_desc);
    }
    (k == 0) ? dprintf(client, "There is no channel in this team.\r\n") : (0);
}

void list_thread(server_t *server, int client, int id)
{
    int i = 0;
    int k = 0;
    int j = 0;

    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]) != 0; i++);
    for (k = 0; strcmp(server->teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]) != 0; k++);
    dprintf(client, "233 List of threads that exist on this channel\r\n");
    delay(1);
    for (; strcmp(server->teams[i].channel[k].thread[j].thread_id, "NULL") != 0;
        j++) {
        dprintf(client, "Thread title -> \"%s\"    Thread ID -> \"%s\"\r\n",
            server->teams[i].channel[k].thread[j].thread_title,
            server->teams[i].channel[k].thread[j].thread_id);
        delay(1);
        dprintf(client, "111|%s|%s|10:20|%s|%s|\r\n",
            server->teams[i].channel[k].thread[j].thread_id,
            server->clients[id].user_id,
            server->teams[i].channel[k].thread[j].thread_title,
            server->teams[i].channel[k].thread[j].thread_content);
        }
    (j == 0) ? dprintf(client, "There is no thread in this channel.\r\n") : (0);
}

void list_replies(server_t *server, int client, int id)
{
    int i = 0;
    int k = 0;
    int j = 0;
    int c = 0;

    for (i = 0; strcmp(server->teams[i].team_id,
        server->clients[id].use_state[0]) != 0; i++);
    for (k = 0; strcmp(server->teams[i].channel[k].channel_id,
        server->clients[id].use_state[1]) != 0; k++);
    for (; strcmp(server->teams[i].channel[k].thread[j].thread_id,
        server->clients[id].use_state[2]) != 0; j++);
    dprintf(client, "234 List of comment that are posted on this thread\r\n");
    delay(1);
    for (; strcmp(server->teams[i].channel[k].thread[j].comment[c], "NULL") != 0
        ; c++) {
        dprintf(client, "Reply -> \"%s\"\r\n",
            server->teams[i].channel[k].thread[j].comment[c]);
        delay(1);
        dprintf(client, "112|%s|%s|10:20|%s\r\n",
            server->teams[i].channel[k].thread[j].thread_id,
            server->clients[id].user_id,
            server->teams[i].channel[k].thread[j].comment[c]);
        }
    (c == 0) ? dprintf(client, "There is no comment in this thread.\r\n") : (0);
}

void list(server_t *server, int client, int id)
{
    if (strcmp(server->command, "/list") == 0) {
        if (!server->clients[id].logged) {
            dprintf(client, "515 User not logged\r\n");
            delay(1);
            dprintf(client, "128|\r\n");
        }
        else if (!count_args(server, 0))
            dprintf(client, "501 Error syntax in parameters or arguments\r\n");
        else if (server->clients[id].use_state[2])
            list_replies(server, client, id);
        else if (server->clients[id].use_state[1] &&
            !server->clients[id].use_state[2])
            list_thread(server, client, id);
        else if (server->clients[id].use_state[0] &&
            !server->clients[id].use_state[1])
            list_channel(server, client, id);
        else if (!server->clients[id].use_state[0])
            list_teams(server, client);
    } else {
        dprintf(client, "501 Error syntax in parameters or arguments\r\n");
    }
}
