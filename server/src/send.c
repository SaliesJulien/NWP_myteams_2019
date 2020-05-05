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

bool if_conversation_exist(server_t *server, int id, char *uuid_str, char *message)
{
    int i = 0;
    int a = 0;

    for (; &server->clients[id].conversation[i] ; i++)
        if (strcmp(server->clients[id].conversation[i].client_id, uuid_str) == 0) {
            for (; server->clients[id].conversation[i].message[a] ; a++);
            server->clients[id].conversation[i].message = realloc(
            server->clients[id].conversation[i].message, (sizeof(char *) * (a + 1)));
            server->clients[id].conversation[i].message[a] = malloc(sizeof(char *)
            * strlen(message));
            strcpy(server->clients[id].conversation[i].message[a], message);
            return (true);
        }
    return (false);
}

void fill_messages(server_t *server, int id, char *uuid_str, char *message)
{
    bool conversation_found = false;
    int i = 0;
    int id_default = id;

    for (int y = 0; y < 2; y++) {
        conversation_found = if_conversation_exist(server, id, uuid_str, message);
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
        id = uuid_index(server, uuid_str);
        uuid_str = server->clients[id_default].user_id;
    }
}

void send_messages(server_t *server, int client, int id)
{
    (void)client;
    char *uuid_str = parse_first_args(server);
    char *message = parse_messages(server);

    if (!uuid_exit(server, uuid_str)) {
        dprintf(1, "User pas trouvé");
        exit (84);
    }
    fill_messages(server, id, uuid_str, message);
    send_notif(server, id, uuid_str);
}
