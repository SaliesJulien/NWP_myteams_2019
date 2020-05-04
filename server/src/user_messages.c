/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** messages_users
*/

#include "server.h"

char *get_command_id(server_t *server)
{
    char *id = malloc(sizeof(char) * 37);
    int k = 0;
    int i = 0;

    for (i = 0; server->command[i] && server->command[i] != ' '; i++);
    for (int j = i + 1; server->command[j] && server->command[j] != '\r'; j++)
        id[k++] = server->command[j];
    return (id);
}

void print(int client, int id, server_t *server, int i)
{
    for (int k = 0; server->clients[id].conversation[i].message[k]; k++)
        dprintf(client,
            "%s\n", server->clients[id].conversation[i].message[k]);
}

void print_messages(server_t *server, int id, char *cmd_id, int client)
{
    for (int i = 0; &server->clients[id].conversation[i]; i++) {
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
    char *cmd_id = get_command_id(server);

    for (int i = 0; i < server->nb_clients; i++) {
        if (strcmp(cmd_id, server->clients[i].user_id) == 0)
            id_exist = true;
    }
    (id_exist == false) ? dprintf(client, "xxx client's ID unknow.\n")
    : print_messages(server, id, cmd_id, client);
}
