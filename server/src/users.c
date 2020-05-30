/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** users
*/

#include "server.h"
#include <time.h>

void print_user_list(server_t *server, int i, bool check, int client)
{
    int logged = 0;

    if (check == false) {
        dprintf(client, "Username : %s    ID : %s\r\n",
            server->clients[i].user_name,
            server->clients[i].user_id);
        logged = (server->clients[i].logged) ? 1 : 0;
        delay(1);
        dprintf(client, "108|%s|%s|%d|\r\n",
        server->clients[i].user_id,
        server->clients[i].user_name, logged);
    }
}

bool check_user_list(server_t *server, int client, int i, bool check)
{
    for (int j = 0; j < server->nb_clients; j++) {
        if (strcmp(server->clients[j].user_name, server->clients[i].user_name)
            == 0 && j != i) {
            print_user_list(server, i, check, client);
            check = true;
            break;
        }
        check = false;
    }
    return (check);
}

void get_list(server_t *server, int client)
{
    int i = 0;
    int logged = 0;
    bool check = false;

    dprintf(client, "202 List of all users existing on the server\r\n");
    for (; i < server->nb_clients; i++) {
        check = check_user_list(server, client, i, check);
        if (check == false) {
            delay(1);
            dprintf(client, "Username : %s    ID : %s\r\n",
                server->clients[i].user_name,
                server->clients[i].user_id);
            logged = (server->clients[i].logged) ? 1 : 0;
            delay(1);
            dprintf(client, "108|%s|%s|%d|\r\n",
                server->clients[i].user_id,
                server->clients[i].user_name, logged);
        }
    }
}

void users_list(server_t *server, int client, int id)
{
    if (strcmp(server->command, "/users") == 0) {
        if (server->clients[id].logged == true) {
            get_list(server, client);
        } else {
            dprintf(client,
                "515 User not logged\r\n");
            delay(1);
            dprintf(server->clients[id].fd_client, "128|\r\n");
        }
    } else {
        dprintf(client, "501 Error syntax in parameters or arguments\r\n");
    }
}
