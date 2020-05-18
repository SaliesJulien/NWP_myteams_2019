/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** messages_users
*/

#include "server.h"

void print(int client, int id, server_t *server, int i)
{
    dprintf(client,
            "205 Conversation with \"username\"\n");
    for (int k = 0; server->clients[id].conversation[i].message[k]; k++) {
        dprintf(client,
            "%s\n", server->clients[id].conversation[i].message[k]);
        dprintf(client, "113|sender_id|10:20|%s|\n",
            server->clients[id].conversation[i].message[k]);
    }
}

void print_messages(server_t *server, int id, char *cmd_id, int client)
{
    for (int i = 0; server->clients[id].conversation[i].client_id != NULL; i++) {
        if (!strcmp(server->clients[id].conversation[i].client_id, cmd_id)) {
            print(client, id, server, i);
            return;
        }
    }
    dprintf(client, "xxx You don't have conversation with this user.\n");
}

void client_mess(server_t *server, int client, int id)
{
    bool id_exist = false;
    char *cmd_id = parse_args(server, 0);

    if (!strcmp(cmd_id, "Bad cmd") || strlen(cmd_id) < 1) {
        dprintf(client, "501 Error syntax in parameters or arguments\n");
        return;
    }
    else {
        for (int i = 0; i < server->nb_clients; i++) {
            if (strcmp(cmd_id, server->clients[i].user_id) == 0)
                id_exist = true;
        }
        if (!id_exist) {
            dprintf(client, "303 User doesn't exist\n");
            dprintf(client, "117|%s|\n", cmd_id);
        }
        else
            print_messages(server, id, cmd_id, client);
    }
}
