/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** client
*/

#include "client.h"

void init_struct_sockaddr(struct sockaddr_in *name, int port, const char *ip)
{
    name->sin_addr.s_addr = inet_addr(ip);
    name->sin_port = htons(port);
    name->sin_family = AF_INET;
}

int create_client_socket(void)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        perror("Socket");
        exit(84);
    }
    return (sock);
}

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
    if (strlen(str) > 0) {
        if (i == server_sock)
            dprintf(sock, "%s\r\n", str);
        else
            dprintf(server_sock, "%s\r\n", str);
    }
    //else {
    //    if (i == server_sock)
    //        dprintf(sock, "Error\r\n");
    //    else
    //        dprintf(server_sock, "Error\r\n");
    //}
}

bool cmd_loop(int server_sock, int sock, char *str, fd_set *set)
{
    init_fd(set, server_sock, sock);
    if ((select(FD_SETSIZE, &set[READING], &set[WRITING], NULL, NULL)) == -1)
        return (true);
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (FD_ISSET(i, &set[READING]) == true) {
            str = calloc(1150, sizeof(char));
            read(i, str, 1150);
            str[strlen(str)-1] = 0;
            if (strncmp(str, "1", 1) == 0)
                pointer_function(str);
            else
                print_fd(server_sock, sock, str, i);
        }
    }
    return (false);
}

void main_loop(int sock, struct sockaddr_in name)
{
    int server_sock = 0;
    socklen_t size = sizeof(name);
    char *str = calloc(256, sizeof(char));
    fd_set set[2];
    bool error = false;

    if ((server_sock = connect(sock, (struct sockaddr *)&name, size) == -1))
        exit(84);
    while (error == false)
        error = cmd_loop(server_sock, sock, str, set);
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