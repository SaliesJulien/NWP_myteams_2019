/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** exec_commands
*/

#include "server.h"

//bool does_id_exist(server_t *server, int id)
//{
    //bool id_exist = false;

    //for (int i = 0; i < server->nb_clients; i++) {
    //    if (strcmp(, server->clients[i].user_id))
    //        id_exist = true;
    //}
    //return (id_exist);
//}

//void print_messages(server_t *server)
//{
//    for (int i = 0; server->clients[id].messages[i])
//}

void client_mess(server_t *server, int client, int id)
{
    (void)id;
    //if (!does_id_exist(server, id)) {
    //    dprintf(client, "xxx client's ID unknow.\r\n")
    //    return;
    //}
    //print_messages(server);
    dprintf(client, "%s\r\n", server->command);
}

void help_client(server_t *server, int client, int id)
{
    (void)server;
    (void)id;
    dprintf(client, "Help.\r\n");
}

void command_not_found(server_t *server, int client, int id)
{
    (void)server;
    (void)id;
    dprintf(client, "500 Syntax error, command unrecognized.\r\n");
}

char *format_cmd(char *str)
{
    char *cmd = NULL;

    if (index(str, ' ') != NULL) {
        cmd = strtok(str, " ");
    } else {
        cmd = strdup(str);
        cmd[strlen(cmd)-2] = 0;
    }
    return (cmd);
}

void exec_commands(server_t *server, int client, int id)
{
    char *cmd = NULL;
    bool found = false;
    cmds_t ptr_command[3] = {{"/logout", remove_client},
        {"/help", help_client}, {"/messages", client_mess}};

    cmd = format_cmd(server->command);
    for (int i = 0; i < 3; i++) {
        if (strcmp(ptr_command[i].command, cmd) == 0) {
            ptr_command[i].ptr(server, client, id);
            found = true;
            break;
        }
    }
    (found == false) ? command_not_found(server, client, id) : (0);
}
