/*
** EPITECH PROJECT, 2020
** server
** File description:
** teams gestion
*/

#include "server.h"

void one_args_bis(server_t *server, int client, int id, char *team)
{
    if (server->clients[id].use_state[0] != NULL &&
        server->clients[id].use_state[1] == NULL) {
        if (!use_channel(server, client, id, team)) {
            dprintf(client, "305 Channel doesn't exist\r\n");
            delay(1);
            dprintf(client, "115|%s|\r\n", team);
        }
    } else if (server->clients[id].use_state[0] == NULL)
        if (!use_team(server, client, id, team)) {
            dprintf(client, "304 Team doesn't exist\r\n");
            delay(1);
            dprintf(client, "114|%s|\r\n", team);
        }
}

void one_args(server_t *server, int client, int id)
{
    char *team = parse_args(server, 0);

    if (server->clients[id].use_state[2] != NULL)
        use_in_thread(server, client, id, team);
    else if (server->clients[id].use_state[1] != NULL &&
        server->clients[id].use_state[2] == NULL) {
        if (!use_thread(server, client, id, team)) {
            dprintf(client, "306 Thread doesn't exist\r\n");
            delay(1);
            dprintf(client, "116|%s|\r\n", team);
        }
    } else
        one_args_bis(server, client, id, team);
    free(team);
}

void use_state_third(server_t *server, int client, int id)
{
    if (count_args(server, 0))
        use_back(server, client, id);
    else
        dprintf(client, "501 Error syntax in parameters or arguments\r\n");
}

void use_state_bis(server_t *server, int client, int id)
{
    if (count_args(server, 2))
        two_args(server, client, id);
    else if (count_args(server, 3))
        three_args(server, id, false, false);
    else
        use_state_third(server, client, id);
}

void use(server_t *server, int client, int id)
{
    if (!server->clients[id].logged) {
        dprintf(client, "515 User not logged\r\n");
        delay(1);
        dprintf(client, "128|\r\n");
    } else if (count_args(server, 1))
        one_args(server, client, id);
    else
        use_state_bis(server, client, id);
}
