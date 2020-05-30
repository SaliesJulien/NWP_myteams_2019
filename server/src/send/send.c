/*
** EPITECH PROJECT, 2020
** send.c
** File description:
** send.c
*/

#include "server.h"

void send_notif(server_t *server, int id, char *uuid_str)
{
    int i = 0;

    for (; i < server->nb_clients; i++) {
        if (!strcmp(server->clients[i].user_id, uuid_str)
            && server->clients[i].active == true)
            dprintf(server->clients[i].fd_client,
                "\"%s\" send you a message.\r\n",
                server->clients[id].user_id);
    }
}

int doubles_nbs(server_t *server, int id)
{
    int compt = 0;

    for (int i = 0; i < server->nb_clients; i++) {
        if (!strcmp(server->clients[i].user_id, server->clients[id].user_id)
            && server->clients[i].active == true)
            compt++;
    }
    return (compt);
}

void succes_messages(server_t *server, int id, char *uuid_str, char *message)
{
    fprintf(server->messages_write, "%s|%s|%s|\n",
        server->clients[id].user_id, uuid_str,
        message);
    server_event_private_message_sended(server->clients[id].user_id, uuid_str,
        message);

    for (int i = 0; i < server->nb_clients; i++)
        if (!strcmp(server->clients[i].user_id, uuid_str) &&
            server->clients[i].active == true)
            dprintf(server->clients[i].fd_client,
                "103|%s|%s|\r\n", server->clients[id].user_id, message);
    delay(1);
    fill_messages(server, id, uuid_str, message);
    send_notif(server, id, uuid_str);
    dprintf(server->clients[id].fd_client, "204 sucessfully sent message\r\n");
    for (int y = 0; y < 2; y++) {
        if (doubles_nbs(server, id) > 0)
            step_succes_messages(server, id);
        id = uuid_index(server, uuid_str);
    }
}

int check_if_user_exist(server_t *server, int id, char *uuid_str, char *message)
{

    if ((!strcmp(uuid_str, "Bad cmd")) || (!strcmp(message, "Bad cmd"))) {
        dprintf(server->clients[id].fd_client,
            "501 Error syntax in parameters or arguments\r\n");
        free(uuid_str);
        free(message);
        return (0);
    }
    if (!uuid_exit(server, uuid_str)) {
        dprintf(server->clients[id].fd_client, "303 User doesn't exist\r\n");
        delay(1);
        dprintf(server->clients[id].fd_client, "117|%s|\r\n", uuid_str);
        free(uuid_str);
        free(message);
        return (0);
    }
    succes_messages(server, id, uuid_str, message);
    return (1);
}

void send_messages(server_t *server, int client, int id)
{
    char *uuid_str = parse_args(server, 0);
    char *message = parse_args(server, 2);

    if (!server->clients[id].logged) {
        dprintf(client, "515 User not logged\r\n");
        delay(1);
        dprintf(client, "128|\r\n");
        free(uuid_str);
        free(message);
        return;
    }
    if (!count_args(server, 2)) {
        dprintf(client, "501 Error syntax in parameters or arguments\r\n");
        free(uuid_str);
        free(message);
        return;
    }
    if (!check_if_user_exist(server, id, uuid_str, message))
        return;
    free(uuid_str);
    free(message);
}
