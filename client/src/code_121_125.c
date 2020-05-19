/*
** EPITECH PROJECT, 2020
** client
** File description:
** replies code
*/

#include "client.h"

void code_121(char const *thread_id, char const *user_id, time_t time,
    char const *thread_title, char const *thread_content)
{
    client_print_thread(thread_id, user_id, time, thread_title,
        thread_content);
}

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

void code_124(char const *thread_id, char const *user_id, time_t time,
    char const *thread_title, char const *thread_content)
{
    client_print_thread_created(thread_id, user_id, time, thread_title,
        thread_content);
}

void code_125(char const *thread_id, char const *user_id, time_t time,
    char const *thread_title, char const *thread_content)
{
    (void)thread_content;
    client_print_reply_created(thread_id, user_id, time, thread_title);
}
