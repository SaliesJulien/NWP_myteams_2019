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
        if (!strcmp(server->clients[i].user_id, uuid_str))
            break;
    }
    dprintf(server->clients[i].fd_client, "\"%s\" send you a message.\n",
        server->clients[id].user_id);
}

void init_next_array(server_t *server, int id, int i)
{
    server->clients[id].conversation[i].client_id = NULL;
    server->clients[id].conversation[i].message = NULL;
}

bool if_conversation_exist(server_t *server, int id, char *uuid_str,
char *message)
{
    int i = 0;
    int a = 0;

    for (; server->clients[id].conversation[i].client_id != NULL ; i++)
        if (!strcmp(server->clients[id].conversation[i].client_id, uuid_str)) {
            for (; server->clients[id].conversation[i].message[a] ; a++);
            server->clients[id].conversation[i].message = realloc(
            server->clients[id].conversation[i].message, (sizeof(char *) *
            (a + 2)));
            server->clients[id].conversation[i].message[a] = malloc(
            sizeof(char) * strlen(message));
            strcpy(server->clients[id].conversation[i].message[a], message);
            server->clients[id].conversation[i].message[a + 1] = NULL;
            return (true);
        }
    return (false);
}

void fill_messages(server_t *server, int id, char *uuid_str, char *message)
{
    int i = 0;
    int id_default = id;

    for (int y = 0; y < 2; y++) {
        if (!if_conversation_exist(server, id, uuid_str, message)) {
            for (; server->clients[id].conversation[i].client_id != NULL; i++);
            server->clients[id].conversation = realloc(
            server->clients[id].conversation, sizeof(messages_t) * (i + 2));
            server->clients[id].conversation[i].client_id = malloc(sizeof(char)
            * 37);
            strcpy(server->clients[id].conversation[i].client_id, uuid_str);
            server->clients[id].conversation[i].message = malloc(
            sizeof(char *));
            server->clients[id].conversation[i].message[0] = malloc(
            sizeof(char *) * strlen(message));
            strcpy(server->clients[id].conversation[i].message[0], message);
            init_next_array(server, id, i + 1);
        }
        id = uuid_index(server, uuid_str);
        uuid_str = server->clients[id_default].user_id;
    }
}

void send_messages(server_t *server, int client, int id)
{
    char *uuid_str = parse_args(server, 0);
    char *message = parse_args(server, 2);

    if ((!strcmp(uuid_str, "Bad cmd") || strlen(uuid_str) < 1) ||
        (!strcmp(message, "Bad cmd") || strlen(message) < 1)) {
        dprintf(client, "501 Error syntax in parameters or arguments\n");
        return;
    }
    if (!uuid_exit(server, uuid_str)) {
        dprintf(client, "303 User doesn't exist\n");
        return;
    }
    fprintf(server->fp, "%s|%s|%s|\n", server->clients[id].user_id, uuid_str, message);
    fill_messages(server, id, uuid_str, message);
    send_notif(server, id, uuid_str);
    dprintf(client, "204 sucessfully sent message\n");
}
