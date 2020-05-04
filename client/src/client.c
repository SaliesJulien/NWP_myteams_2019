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

int create_client_socket()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        perror("Socket");
        exit(84);
    }
    return (sock);
}

void main_loop(int sock, struct sockaddr_in name)
{
    int server_sock = 0;
    socklen_t size = sizeof(name);
    char *str = calloc(256, sizeof(char));

    server_sock = connect(sock, (struct sockaddr *)&name, size);
    if (server_sock == -1) {
        perror("Connect");
        exit(84);
    }
    dprintf(sock, "Salut !\n");
    while (strcmp(str, "STOP") != 0) {
        read(server_sock, str, 256);
        dprintf(sock, str);
        str = calloc(256, sizeof(char));
    }
    close(server_sock);
    close(sock);
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