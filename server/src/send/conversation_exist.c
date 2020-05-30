/*
** EPITECH PROJECT, 2020
** send.c
** File description:
** send.c
*/

#include "server.h"

void conversation_exist(server_t *server, int id, char *message, int i)
{
    int a = 0;

    for (; server->clients[id].conversation[i].message[a] != NULL;
        a++);
    server->clients[id].conversation[i].message = realloc(
    server->clients[id].conversation[i].message, (sizeof(char *) *
        (a + 2)));
    server->clients[id].conversation[i].message[a] = malloc(
        sizeof(char) * (strlen(message) + 39));
    strcpy(server->clients[id].conversation[i].message[a], message);
    strcat(server->clients[id].conversation[i].message[a], "|");
    strcat(server->clients[id].conversation[i].message[a],
        server->clients[id].user_id);
    server->clients[id].conversation[i].nb_messages++;
    server->clients[id].conversation[i].message[a + 1] = NULL;
}

bool if_conversation_exist(server_t *server, int id, char *uuid_str,
    char *message)
{
    int i = 0;

    for (; server->clients[id].conversation[i].client_id != NULL; i++)
        if (!strcmp(server->clients[id].conversation[i].client_id, uuid_str)) {
            conversation_exist(server, id, message, i);
            return (true);
        }
    return (false);
}

void conversation_not_exist(server_t *server, int id, char *uuid_str,
    char *message)
{
    int i = 0;

    for (; server->clients[id].conversation[i].client_id != NULL; i++);
    server->clients[id].conversation = realloc(
    server->clients[id].conversation, sizeof(messages_t) * (i + 2));
    server->clients[id].conversation[i].client_id = malloc(sizeof(char)
    * 37);
    strcpy(server->clients[id].conversation[i].client_id, uuid_str);
    server->clients[id].conversation[i].message = malloc(
        sizeof(char *) * 2);
    server->clients[id].conversation[i].message[0] = malloc(
        sizeof(char) * (strlen(message) + 39));
    strcpy(server->clients[id].conversation[i].message[0], message);
    strcat(server->clients[id].conversation[i].message[0], "|");
    strcat(server->clients[id].conversation[i].message[0],
        server->clients[id].user_id);
    server->clients[id].conversation[i].nb_messages = 1;
    server->clients[id].conversation[i].message[1] = NULL;
    server->clients[id].conversation[i + 1].client_id = NULL;
    server->clients[id].nb_conversation++;
}

void fill_messages(server_t *server, int id, char *uuid_str, char *message)
{
    int user_nb = 0;
    int id_default = id;

    user_nb = (!strcmp(server->clients[id].user_id, uuid_str)) ? 1 : 2;
    for (int y = 0; y < user_nb; y++) {
        if (!if_conversation_exist(server, id, uuid_str, message)) {
            conversation_not_exist(server, id, uuid_str, message);
        }
        id = uuid_index(server, uuid_str);
        uuid_str = server->clients[id_default].user_id;
    }
}

void step_succes_messages(server_t *server, int id)
{
    for (int i = 0; i < server->nb_clients; i++)
        if (!strcmp(server->clients[i].user_id,
            server->clients[id].user_id)
            && server->clients[i].active == true)
            server->clients[i].conversation =
                server->clients[id].conversation;
}