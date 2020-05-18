/*
** EPITECH PROJECT, 2020
** client
** File description:
** replies code
*/

#include "client.h"

void code_116(char const *first, char const *second, char const *third,
    char const *four)
{
    (void)second;
    (void)third;
    (void)four;
    client_error_unknown_thread(first);
}

void code_117(char const *first, char const *second, char const *third,
    char const *four)
{
    (void)second;
    (void)third;
    (void)four;
    client_error_unknown_user(first);
}

void code_118(char const *first, char const *second, int third)
{
    client_print_user(first, second, third);
}

void code_119(char const *first, char const *second, char const *third,
    char const *four)
{
    (void)four;
    client_print_team(first, second, third);
}

void code_120(char const *first, char const *second, char const *third,
    char const *four)
{
    (void)four;
    client_print_channel(first, second, third);
}