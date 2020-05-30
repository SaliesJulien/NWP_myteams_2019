/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** handle_commands
*/

#include "client.h"

void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();

    while (clock() < start_time + milli_seconds);
}

char *catch_signals(int sock, char *str, int i)
{
    signal(SIGINT, control_c);
    signal(SIGHUP, terminal_killed);
    if (oops == false) {
        dprintf(sock, "/logout\r\n");
        delay(1);
    }
    str = calloc(1150, sizeof(char));
    read(i, str, 1150);
    if (strlen(str) > 1)
        str[strlen(str) - 1] = 0;
    if (str[strlen(str) - 1] == '\r')
        str[strlen(str) - 1] = 0;
    return (str);
}

bool check_commands(int server_sock, int sock, char *str, int i)
{
    str = catch_signals(sock, str, i);
    if (strncmp(str, "221", 3) == 0) {
        print_fd(server_sock, sock, str, i);
        close(sock);
        free(str);
        return (true);
    } else if (strncmp(str, "1", 1) == 0) {
        pointer_function(str);
    } else {
        print_fd(server_sock, sock, str, i);
    }
    free(str);
    return (false);
}

bool cmd_loop(int server_sock, int sock, char *str, fd_set *set)
{
    init_fd(set, server_sock, sock);
    if ((select(FD_SETSIZE, &set[READING], &set[WRITING], NULL, NULL)) == -1)
        return (true);
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (FD_ISSET(i, &set[READING]) == true) {
            return ((check_commands(server_sock, sock, str, i) == true) ?
                (true) : (0));
        }
    }
    return (false);
}
