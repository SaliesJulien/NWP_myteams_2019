/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** function_handling
*/

#include "client.h"

char *get_args(char *command, int nb)
{
    int i = 0;
    int k = 0;
    int count = 0;
    char *temp = malloc(sizeof(char) * 40);

    for (;command[i] && (count == nb); i++)
        if (command[i] == '|')
            count++;
    if (count < nb)
        return (NULL);
    for (;command[i] && (command[i] != '|'); i++)
        temp[k++] = command[i];
    temp[k] = '\0';
    printf("%s\n", temp);
    return (temp);
}

void pointer_function(int server_sock, int sock, char *str)
{
    (void)server_sock;
    (void)sock;
    (void)str;
    //simple_replies_t ptr_simple[20] = {{"101", code_101}, {"102", code_102},
    //    {"103", code_103}, {"104", code_104}, {"105", code_105},
    //    {"106", code_106}, {"109", code_109}, {"110", code_110},
    //    {"114", code_114}, {"115", code_115}, {"116", code_116},
    //    {"117", code_117}, {"119", code_119}, {"120", code_120},
    //    {"122", code_122}, {"123", code_123}, {"126", code_126},
    //    {"127", code_127}, {"128", code_128}, {"129", code_129}};

    //time_replies_t ptr_time[6] = {{"107", code_107}, {"111", code_111},
    //    {"112", code_112}, {"121", code_121}, {"124", code_124},
    //    {"125", code_125}};
}