/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** login
*/

#include "server.h"

void send_notification_login(server_t *server)
{
    for (int i = 0; i < server->nb_clients; i++)
        dprintf(server->clients[i].fd_client, "101|%s|%s|\n",
            server->clients[i].user_id, server->clients[i].user_name);
}

bool check_exist(server_t *server, int client, int id, int i)
{
    if ((strcmp(server->clients[i].user_name,
        server->clients[id].user_name) == 0) && (i != id)) {
        if (server->clients[i].active == false) {
            server->clients[i].active = true;
            server->clients[i].logged = true;
            server->clients[i].fd_client = server->clients[id].fd_client;
            server->clients[id].fd_client = -1;
            server->clients[id].active = false;
            dprintf(client, "230 Succesfull login\r\n");
            server_event_user_logged_in(server->clients[i].user_id);
            send_notification_login(server);
            return (true);
        } else {
            dprintf(client, "330 Client already connected\r\n");
            dprintf(client, "129|\r\n");
            return (true);
        }
    }
    return (false);
}

void find_uuid(server_t *server, int client, int id)
{
    bool check = false;

    for (int i = 0; i < server->nb_clients; i++) {
        if ((check_exist(server, client, id, i)) == true) {
            check = true;
            break;
        }
    }
    if (check == false) {
        strcpy(server->clients[id].user_id, generate_id());
        dprintf(client, "230 Succesfull login\r\n");
        server->clients[id].logged = true;
        server_event_user_created(server->clients[id].user_id,
            server->clients[id].user_name);
        send_notification_login(server);
    }
}

void login_user(server_t *server, int client, int id)
{
    if (strlen(parse_args(server, 0)) > 32) {
        dprintf(client, "530 Authentification failed, \
        name length longer than 32 characters\r\n");
    }
    else {
        strcpy(server->clients[id].user_name, parse_args(server, 0));
        if (strcmp(server->clients[id].user_name, "Bad cmd") != 0)
            find_uuid(server, client, id);
        else
            dprintf(client,
                "501 Error syntax in parameters or arguments\r\n");
    }
}
