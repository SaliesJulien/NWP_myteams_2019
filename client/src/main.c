/*
** EPITECH PROJECT, 2020
** main file
** File description:
** main
*/

#include "client.h"

int main(int ac, char **av)
{
    //dprintf(1, "%s\n", get_args("102|caca|pipi", 0));
    help(ac, av);
    error_handling(ac, av);
    client_side(av);
    return (0);
}
