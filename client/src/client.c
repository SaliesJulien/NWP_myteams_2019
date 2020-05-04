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

void cmd_loop(int server_sock, int sock, char *str)
{
    int i = 256;

    while (true) {
        read(sock, str, i);
        str[strlen(str)-1] = 0;
        printf("%s\r\n", str);
        i = 256;
        str = calloc(i, sizeof(char));
        read(server_sock, str, i);
        str[strlen(str)-1] = 0;
        dprintf(sock, "%s\r\n", str);
        if ((strcmp(str, "/logout")) == 0)
            break;
        if ((strcmp(str, "/help")) == 0)
            i = 1085;
        str = calloc(i, sizeof(char));
    }
}

void main_loop(int sock, struct sockaddr_in name)
{
    int server_sock = 0;
    socklen_t size = sizeof(name);
    char *str = calloc(256, sizeof(char));

    if ((server_sock = connect(sock, (struct sockaddr *)&name, size) == -1))
        exit(84);
    cmd_loop(server_sock, sock, str);
    str = calloc(256, sizeof(char));
    read(sock, str, 256);
    str[strlen(str)-1] = 0;
    printf("%s\r\n", str);
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
