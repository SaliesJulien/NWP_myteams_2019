/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** control_c signal
*/

#include "client.h"

void control_c(int __attribute__((unused)) contrl)
{
    printf("\n");
}

void terminal_killed(int __attribute__((unused)) contrl)
{
    oops = false;
}

int count_arg_length(char *command, int i)
{
    int k = 0;

    for (;command[i] && command[i] != '|'; i++)
        k++;
    return (k);
}

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
