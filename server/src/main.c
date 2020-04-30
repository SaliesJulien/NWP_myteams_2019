/*
** EPITECH PROJECT, 2020
** main file
** File description:
** main
*/

#include "server.h"

int main(int ac, char **av)
{
    help(ac, av);
    error_handling(ac, av);
    start_server(av);
    return (0);
}
