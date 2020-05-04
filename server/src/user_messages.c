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

void print_messages(server_t *server, int id, char *cmd_id, int client)
{
    //(void)server;
    //(void)id;
    //(void)cmd_id;
    int i = 0;

    while (strcmp(server->clients[id].message[i].client_id, cmd_id)) {
        if (i > server->nb_clients) {
            dprintf(client, "xxx You don't have conversation with this user.\r\n");
            return;
        }
        i++;
    }
    for (int k = 0; server->clients[id].message[i].message[k]; k++)
        dprintf(client, "message %d: %s\n", k, server->clients[id].message[i].message[k]);
}

bool does_id_exist(server_t *server, int id, int client)
{
    bool id_exist = false;
    char *cmd_id = get_command_id(server);

    for (int i = 0; i < server->nb_clients; i++) {
        if (strcmp(cmd_id, server->clients[i].user_id) == 0)
            id_exist = true;
    }
    (id_exist == false) ? (0) : print_messages(server, id, cmd_id, client);
    return (id_exist);
}

void client_mess(server_t *server, int client, int id)
{
    //server->clients[id].message[1] = {{"cc", "coucou"}};
    (void)id;
    if (!does_id_exist(server, id, client))
        dprintf(client, "xxx client's ID unknow.\r\n");
}