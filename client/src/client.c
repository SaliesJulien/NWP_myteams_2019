/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** client
*/

#include "client.h"

void init_fd(fd_set *set, int server_sock, int sock)
{
    FD_ZERO(&set[READING]);
    FD_ZERO(&set[WRITING]);
    FD_SET(server_sock, &set[READING]);
    FD_SET(server_sock, &set[WRITING]);
    FD_SET(sock, &set[READING]);
    FD_SET(sock, &set[WRITING]);
}

void print_fd(int server_sock, int sock, char *str, int i)
{
    char *cmd = strstr(str, "\r\n1");

    if (i == server_sock) {
        dprintf(sock, "%s\r\n", str);
    } else {
        if (cmd != NULL) {
            str[strlen(str) - strlen(cmd)] = 0;
            dprintf(server_sock, "%s\r\n", str);
        } else {
            dprintf(server_sock, "%s\r\n", str);
        }
    }
}

void main_loop(int sock, struct sockaddr_in name)
{
    int server_sock = 0;
    socklen_t size = sizeof(name);
    char *str = calloc(256, sizeof(char));
    fd_set set[2];
    bool error = false;
    oops = true;

    if ((server_sock = connect(sock, (struct sockaddr *)&name, size) == -1)) {
        free(str);
        return;
    }
    while (error == false)
        error = cmd_loop(server_sock, sock, str, set);
    free(str);
}

int client_side(char **argv)
{
    int sock = 0;
    int port = atoi(argv[2]);
    struct sockaddr_in name;

    sock = create_client_socket();
    init_struct_sockaddr(&name, port, argv[1]);
    main_loop(sock, name);
    return (0);
}
