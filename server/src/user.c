/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** user
*/

#include "server.h"

bool find_user(server_t *server, char *user_id, int id)
{
    char *str = calloc(100, sizeof(char));

    strcat(str, "203 User infos\nUser name -> ");
    for (int i = 0; i < server->nb_clients; i++) {
        if (strcmp(user_id, server->clients[i].user_id) == 0) {
            strcat(str, server->clients[i].user_name);
            dprintf(server->clients[id].fd_client, "%s\r\n", str);
            delay(1);
            dprintf(server->clients[id].fd_client, "118|%s|%s|%d|\r\n",
                server->clients[i].user_id,
                server->clients[i].user_name,
                (server->clients[i].logged) ? 1 : 0);
            return (true);
        }
    }
    return(false);
}

void user(server_t *server, int client, int id)
{
    char *user_id = parse_args(server, 0);

    if (server->clients[id].logged == false) {
        dprintf(client, "515 User not logged\r\n");
    } else if (strcmp(user_id, "Bad cmd") != 0) {
        if ((find_user(server, user_id, id)) == false) {
            dprintf(client, "303 User doesn't exist\r\n");
            delay(1);
            dprintf(client, "117|%s|\r\n", user_id);
        }
    } else {
        dprintf(client, "501 Error syntax in parameters or arguments\r\n");
    }
    free(user_id);
}
