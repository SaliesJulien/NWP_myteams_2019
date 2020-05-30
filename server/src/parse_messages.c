/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** parse_content
*/

#include "server.h"

void malloc_messages(server_t *server, char *sender, char *receiver)
{
    server->clients[uuid_index(server, sender)].conversation =
        malloc(sizeof(messages_t));
    server->clients[uuid_index(server, receiver)].conversation =
        malloc(sizeof(messages_t));
    server->clients[uuid_index(server, receiver)].conversation[0].client_id
        = NULL;
    server->clients[uuid_index(server, sender)].conversation[0].client_id
        = NULL;
}

server_t *parse_messages(server_t *server, char *command)
{
    char *receiver = strtok(command, "|");
    char *sender = strtok(NULL, "|");
    char *message = strtok(NULL, "|");

    if (uuid_index(server, sender) != uuid_index(server, receiver) &&
        server->clients[uuid_index(server, sender)].nb_conversation == 0)
        malloc_messages(server, sender, receiver);
    else if (uuid_index(server, sender) == uuid_index(server, receiver)) {
        server->clients[uuid_index(server, sender)].conversation =
            malloc(sizeof(messages_t));
        server->clients[uuid_index(server, receiver)].conversation[0].client_id
            = NULL;
        server->clients[uuid_index(server, sender)].conversation[0].client_id
            = NULL;
    }
    fill_messages(server, uuid_index(server, sender), receiver, message);
    return (server);
}