/*
** EPITECH PROJECT, 2020
** client
** File description:
** replies code
*/

#include "client.h"

void code_111(char const *thread_id, char const *user_id, time_t time,
    char const *thread_title, char const *thread_content)
{
    client_channel_print_threads(thread_id, user_id, time,
        thread_title, thread_content);
}

void code_112(char const *thread_id, char const *user_id, time_t time,
    char const *thread_title, char const *thread_content)
{
    (void)thread_content;
    client_thread_print_replies(thread_id, user_id, time, thread_title);
}

void code_113(char const *first, char const *second, time_t time,
    char const *third,char const *fourth)
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