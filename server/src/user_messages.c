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
    for (int k = 0; server->clients[id].messages[i].message[k]; k++)
        dprintf(client, "%s\n", server->clients[id].messages[i].message[k]);
}

void print_messages(server_t *server, int id, char *cmd_id, int client)
{
    for (int i = 0; server->clients[id].messages[i].client_id; i++) {
        if (strcmp(server->clients[id].messages[i].client_id, cmd_id) == 0) {
            print(client, id, server, i);
            return;
        }
    }
    dprintf(client, "xxx You don't have conversation with this user.\n");
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

/*void init_mock(server_t *server, int id)
{
    server->clients[id].messages = malloc(sizeof(messages_t) * 50);
    server->clients[id].messages[0].client_id = "cc";
    server->clients[id].messages[0].message = malloc(sizeof(char *) * 10);

    server->clients[id].messages[0].message[0] = malloc(sizeof(char) * 10);
    strcpy(server->clients[id].messages[0].message[0], "Julien");
    server->clients[id].messages[0].message[1] = malloc(sizeof(char) * 10);
    strcpy(server->clients[id].messages[0].message[1], "Lucas");
    server->clients[id].messages[0].message[2] = malloc(sizeof(char) * 10);
    strcpy(server->clients[id].messages[0].message[2], "Hugo");
    server->clients[id].conv_nb++;
}*/

void client_mess(server_t *server, int client, int id)
{
    //init_mock(server, id);
    if (!does_id_exist(server, id, client))
        dprintf(client, "xxx client's ID unknow.\n");
}