/*
** EPITECH PROJECT, 2020
** client
** File description:
** replies code
*/

#include "client.h"

void code_122(char const *first, char const *second, char const *third,
    char const *four)
{
    (void)four;
    client_print_team_created(first, second, third);
}

void code_123(char const *first, char const *second, char const *third,
    char const *four)
{
    (void)four;
    client_print_channel_created(first, second, third);
}

void free_all(char *second, char *third, char *fourth, char *fifth)
{
    free(second);
    free(third);
    free(fourth);
    free(fifth);
}

void to_long_arg_command(char *code, char *str)
{
    char *first = get_args(str, 1);
    char *second = get_args(str, 2);
    char *third = get_args(str, 3);
    char *fourth = get_args(str, 4);
    char *fifth = get_args(str, 5);

    if (strncmp("107", code, 3) == 0)
        client_event_thread_created(first, second, time(NULL), fourth, fifth);
    if (strncmp("111", code, 3) == 0)
        client_channel_print_threads(first, second, time(NULL), fourth, fifth);
    if (strncmp("112", code, 3) == 0)
        client_thread_print_replies(first, second, time(NULL), fourth);
    if (strncmp("121", code, 3) == 0)
        client_print_thread(first, second, time(NULL), fourth, fifth);
    if (strncmp("124", code, 3) == 0)
        client_print_thread_created(first, second, time(NULL), fourth, fifth);
    if (strncmp("125", code, 3) == 0)
        client_print_reply_created(first, second, time(NULL), fourth);
    free(first);
    free_all(second, third, fourth, fifth);
}