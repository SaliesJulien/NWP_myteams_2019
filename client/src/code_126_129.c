/*
** EPITECH PROJECT, 2020
** client
** File description:
** replies code
*/

#include "client.h"

void code_126(char const *first, char const *second, char const *third,
    char const *four)
{
    (void)third;
    (void)four;
    client_print_subscribed(first, second);
}

void code_127(char const *first, char const *second, char const *third,
    char const *four)
{
    (void)third;
    (void)four;
    client_print_unsubscribed(first, second);
}

void code_128(char const *first, char const *second, char const *third,
    char const *four)
{
    (void)first;
    (void)second;
    (void)third;
    (void)four;
    client_error_unauthorized();
}

void code_129(char const *first, char const *second, char const *third,
    char const *four)
{
    (void)first;
    (void)second;
    (void)third;
    (void)four;
    client_error_already_exist();
}