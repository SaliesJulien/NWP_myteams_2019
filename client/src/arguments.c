/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** arguments
*/

#include "client.h"

void help(int ac, char **av)
{
    if (ac == 2 && (!strcmp(av[1], "-h") ||
        !strcmp(av[1], "-help") || !strcmp(av[1], "--help"))) {
        puts("USAGE: ./myteams_cli ip port");
        puts("\tip is the server ip address on wich the server sockets listens"
        );
        puts("\tport is the port number on wich the server socket listens");
        exit(0);
    }
}

void error_handling(int ac, char **av)
{
    if (ac != 3) {
        puts("Arguments error");
        exit(84);
    }
    else if (atoi(av[2]) == 0) {
        puts("Port unknown");
        exit(84);
    }
}