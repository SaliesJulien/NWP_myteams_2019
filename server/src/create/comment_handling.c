/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

void send_notif_channel_client(server_t *server, int i, int id, char *name)
{
    int a = 0;
    int count = 0;
    int k = channel_nb(server, id, i);
    int j = thread_nb(server, id, i, k);

    fprintf(server->comment_write, "%s|%s|%s|%s|\r\n",
        server->teams[i].team_id, server->teams[i].channel[k].channel_id,
        server->teams[i].channel[k].thread[j].thread_id, name);
    server_event_thread_new_message(
        server->teams[i].channel[k].thread[j].thread_id,
        server->clients[id].user_id,
        server->teams[i].channel[k].thread[j].thread_content);
    for (; strcmp(server->teams[i].members[a].name, "NULL") != 0; a++) {
        for (count = 0; strcmp(server->clients[count].user_name,
            server->teams[i].members[a].name) != 0; count++);
        dprintf(server->clients[count].fd_client,
            "104|%s|%s|%s|%s|\r\n", server->teams[i].team_id,
            server->teams[i].channel[k].thread[j].thread_id,
            server->clients[id].user_id,
            server->teams[i].channel[k].thread[j].thread_content);
    }
}

void send_notif_channel_server(server_t *server, int i, int id, int k)
{
    int j = thread_nb(server, id, i, k);

    dprintf(server->clients[id].fd_client,
        "228 You succesfully posted a comment in \"%s\"\r\n",
        server->teams[i].channel[k].thread[j].thread_title);
    delay(1);
    dprintf(server->clients[id].fd_client,
        "125|%s|%s|%s|%s|\r\n",
        server->teams[i].channel[k].thread[j].thread_id,
        server->clients[id].user_id, "10:00",
        server->teams[i].channel[k].thread[j].thread_content);
    server->teams[i].channel[k].thread[j].nb_comments++;
}

void create_new_comment(server_t *server, int id, char *name)
{
    int i = team_nb(server, id);
    int k = channel_nb(server, id, i);
    int j = thread_nb(server, id, i, k);
    int count = comment_nb(server, i, k, j);

    if (!user_subscribed(server, i, id, "comment"))
        return;
    server->teams[i].channel[k].thread[j].comment =
        realloc(server->teams[i].channel[k].thread[j].comment,
        sizeof(char *) * (count + 2));
    server->teams[i].channel[k].thread[j].comment[count] =
        realloc(server->teams[i].channel[k].thread[j].comment[count],
            sizeof(char) * strlen(name) + 1);
    server->teams[i].channel[k].thread[j].comment[count + 1] =
        malloc(sizeof(char) * 5);
    strcpy(server->teams[i].channel[k].thread[j].comment[count], name);
    strcpy(server->teams[i].channel[k].thread[j].comment[count + 1], "NULL");
    send_notif_channel_server(server, i, id, k);
    send_notif_channel_client(server, i, id, name);
}

void comment_error(server_t *server, char *team_name, int id)
{
    if (count_args(server, 1))
        if (strlen(team_name) > DEFAULT_BODY_LENGTH)
            dprintf(server->clients[id].fd_client,
                "532 Post failed, body length longer than 512 characters\r\n");
        else if (strcmp(team_name, "Bad cmd"))
            create_new_comment(server, id, team_name);
        else
            dprintf(server->clients[id].fd_client,
                "501 Syntax error in parameters or arguments\r\n");
    else
        dprintf(server->clients[id].fd_client,
            "501 Syntax error in parameters or arguments\r\n");
}
