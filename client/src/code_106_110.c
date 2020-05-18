/*
** EPITECH PROJECT, 2020
** client
** File description:
** replies code
*/

#include "client.h"

void code_106(char const *first, char const *second, char const *third,
    char const *four)
{
    (void)four;
    client_event_channel_created(first, second, third);
}

void code_107(char const *thread_id, char const *use_id, time_t time,
    char const *thread_title, char const *thread_content)
{

}

void code_108(char const *first, char const *second, int user_statuss)
{
    client_print_users(first, second, user_status);
}

void code_109(char const *first, char const *second, char const *third,
    char const *four)
{
    (void)four;
    client_print_teams(first, second, third);
}

void code_110(char const *first, char const *second, char const *third,
    char const *four)
{
    (void)four;
    client_team_print_channels(first, second, third);
}