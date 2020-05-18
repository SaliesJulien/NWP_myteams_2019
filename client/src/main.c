/*
** EPITECH PROJECT, 2020
** main file
** File description:
** main
*/

#include "client.h"

int main(int ac, char **av)
{
    get_args("105|team_id|team_name|team_description", 2);
    help(ac, av);
    error_handling(ac, av);
    client_side(av);
    return (0);
}
