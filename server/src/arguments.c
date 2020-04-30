/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** arguments
*/

#include "server.h"

void help(int ac, char **av)
{
    if (ac == 2 && (!strcmp(av[1], "-h") ||
        !strcmp(av[1], "-help") || !strcmp(av[1], "--help"))) {
        puts("USAGE: ./myteams_server port");
        puts("\t\tport is the port number on wich the server socket listens.");
        exit(0);
    }
}

void error_handling(int ac, char **av)
{
    if (ac != 2) {
        puts("Arguments error");
        exit(84);
    }
    if (atoi(av[1]) == 0) {
        puts("Port unknown");
        exit(84);
    }
}