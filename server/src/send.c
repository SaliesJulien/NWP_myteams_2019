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
            for (size_t j = i; server->command[j] != '"'; j++) {
                message[compt] = server->command[j];
                compt++;
            }
        }
    }
    message[compt] = '\0';
    return (message);
}

void send_messages(server_t *server, int client, int id)
{
    (void)id;
    (void)client;
    char *uuid_str = parse_first_args(server);
    char *message = parse_messages(server);
    dprintf(1, "Messages %s", server->command);
}