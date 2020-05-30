/*
** EPITECH PROJECT, 2020
** client
** File description:
** replies code
*/

#include "client.h"

void code_101(char const *first, char const *second,
    char const *third, char const *four)
{
    (void)third;
    (void)four;
    client_event_loggedin(first, second);
}

void code_102(char const *first, char const *second, char const *third,
    char const *four)
{
    (void)third;
    (void)four;
    client_event_loggedout(first, second);
}

void code_103(char const *first, char const *second, char const *third,
    char const *four)
{
    (void)third;
    (void)four;
    client_event_private_message_received(first, second);
}

void code_104(char const *first, char const *second, char const *third,
    char const *four)
{
    client_event_thread_message_received(first, second, third, four);
}

void code_105(char const *first, char const *second, char const *third,
    char const *four)
{
    (void)four;
    client_event_team_created(first, second, third);
}