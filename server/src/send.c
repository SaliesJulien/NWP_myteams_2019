/*
** EPITECH PROJECT, 2020
** send.c
** File description:
** send.c
*/

#include "server.h"

char *parse_messages(server_t *server)
{
    char *message = calloc(DEFAULT_BODY_LENGTH, sizeof(char));
    int quotes = 0;
    int compt = 0;

    for (size_t i = 0; i < strlen(server->command) && quotes < 3; i++) {
        if (server->command[i] == '"')
            quotes++;
        if (quotes > 2) {
            i++;
            for (size_t j = i; server->command[j] != '"'; j++) {
                message[compt] = server->command[j];
                compt++;
            }
        }
    }
    message[compt] = '\0';
    return (message);
}
// /send [“user_uuid”] [“message_body”] : send a message to a user

void send_messages(server_t *server, int client, int id)
{
    (void)client;
    char *uuid_str = parse_first_args(server);
    char *message = parse_messages(server);
    int i = 0;
    int a = 0;
    bool conversation_found = false;

    if (!uuid_exit(server, uuid_str)) {
        dprintf(1, "User pas trouvé");
        exit (84);
    }
    for (; &server->clients[id].conversation[i] ; i++) {
        if (strcmp(server->clients[id].conversation[i].client_id, uuid_str) == 0) {
            conversation_found = true;
            for (; server->clients[id].conversation[i].message[a] ; a++);
            server->clients[id].conversation[i].message = realloc(
            server->clients[id].conversation[i].message, (sizeof(char *) * (a + 1)));
            server->clients[id].conversation[i].message[a] = malloc(sizeof(char *)
            * strlen(message));
            strcpy(server->clients[id].conversation[i].message[a], message);
            break;
        }
    }
    if (conversation_found == false) {
        server->clients[id].conversation = realloc(server->clients[id].conversation,
        sizeof(messages_t) * (i + 1));
        server->clients[id].conversation[i].client_id = malloc(sizeof(char) * 37);
        strcpy(server->clients[id].conversation[i].client_id, uuid_str);
        server->clients[id].conversation[i].message = malloc(sizeof(char *));
        server->clients[id].conversation[i].message[0] = malloc(sizeof(char *) *
        strlen(message));
        strcpy(server->clients[id].conversation[i].message[0], message);
    }
    dprintf(1, "Finish\n");
}
