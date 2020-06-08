/*
** EPITECH PROJECT, 2020
** client
** File description:
** replies code
*/

#include "client.h"

void code_113(char const *first, char const *second, time_t time,
    char const *third, char const *fourth)
{
    (void)second;
    (void)fourth;
    client_private_message_print_messages(first, time, third);
}

void code_114(char const *first, char const *second, char const *third,
    char const *four)
{
    (void)second;
    (void)third;
    (void)four;
    client_error_unknown_team(first);
}

void code_115(char const *first, char const *second, char const *third,
    char const *four)
{
    (void)second;
    (void)third;
    (void)four;
    client_error_unknown_channel(first);
}