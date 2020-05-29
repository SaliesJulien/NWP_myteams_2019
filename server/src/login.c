/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** login
*/

#include "server.h"

void send_notification_login(server_t *server, int id)
{
    for (int i = 0; i < server->nb_clients; i++)
        if (server->clients[i].active == true)
            dprintf(server->clients[i].fd_client, "101|%s|%s|\r\n",
                server->clients[id].user_id, server->clients[id].user_name);
    server_event_user_logged_in(server->clients[id].user_id);
}

void desactivate_client(server_t *server, int i, int id)
{
    server->clients[i].active = true;
    server->clients[i].logged = true;
    server->clients[i].fd_client = server->clients[id].fd_client;
}

bool check_exist(server_t *server, char *arg, int id, int i)
{
    if ((strcmp(server->clients[i].user_name,
        arg) == 0) && (i != id)) {
        if (server->clients[i].active == false) {
            desactivate_client(server, i, id);
            server->clients[id].fd_client = -1;
            server->clients[id].active = false;
            server->nb_clients--;
            dprintf(server->clients[id].fd_client, "230 Succesfull login\r\n");
            send_notification_login(server, i);
            return (true);
        } else {
            strcpy(server->clients[id].user_name, arg);
            strcpy(server->clients[id].user_id, server->clients[i].user_id);
            dprintf(server->clients[id].fd_client, "230 Succesfull login\r\n");
            delay(1);
            server->clients[id].logged = true;
            send_notification_login(server, id);
            return (true);
        }
    }
    return (false);
}

void find_uuid(server_t *server, int client, int id, char *arg)
{
    bool check = false;
    char *id_generate = generate_id();

    for (int i = 0; i < server->nb_clients; i++) {
        if ((check_exist(server, arg, id, i)) == true) {
            check = true;
            break;
        }
    }
    if (check == false) {
        strcpy(server->clients[id].user_name, arg);
        strcpy(server->clients[id].user_id, id_generate);
        dprintf(client, "230 Succesfull login\r\n");
        delay(1);
        server->clients[id].logged = true;
        server_event_user_created(server->clients[id].user_id,
            server->clients[id].user_name);
        send_notification_login(server, id);
    }
    free(id_generate);
}

void login_user(server_t *server, int client, int id)
{
    char *arg = parse_args(server, 0);

    if (strlen(arg) > 32) {
        dprintf(client, "530 Authentification failed, \
        name length longer than 32 characters\r\n");
    } else if (!count_args(server, 1)) {
        dprintf(client, "501 Error syntax in parameters or arguments\r\n");
    } else {
        if (strcmp(arg, "Bad cmd") != 0) {
            find_uuid(server, client, id, arg);
        } else {
            dprintf(client,
                "501 Error syntax in parameters or arguments\r\n");
        }
    }
    free(arg);
}
