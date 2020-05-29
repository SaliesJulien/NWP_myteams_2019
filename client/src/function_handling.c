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
    char *temp = NULL;

    for (;command[i] && command[i] != '\r'; i++) {
        if (count == nb)
            break;
        (command[i] == '|') ? count++ : (0);
    }
    if (count < nb)
        return (NULL);
    temp = malloc(sizeof(char) * count_arg_length(command, i) + 1);
    for (;command[i] && command[i] != '|'; i++)
        temp[k++] = command[i];
    temp[k] = '\0';
    if (temp[0] == '\0') {
        free(temp);
        return (NULL);
    }
    return (temp);
}

void others_commands(char *code, char *str)
{
    char *first_arg = get_args(str, 1);
    char *second_arg = get_args(str, 2);
    char *third_arg = get_args(str, 3);

    if (strncmp("108", code, 3) == 0)
        code_108(first_arg, second_arg, atoi(third_arg));
    if (strncmp("118", code, 3) == 0)
        code_118(first_arg, second_arg, atoi(third_arg));
    if (strncmp("113", code, 3) == 0)
        code_113(first_arg, NULL, time(NULL), third_arg, NULL);
    free(first_arg);
    free(second_arg);
    free(third_arg);
}

void free_content(char *third_arg, char *fourth_arg, char *fifth_arg)
{
    free(third_arg);
    free(fourth_arg);
    free(fifth_arg);
}

void find_function(simple_replies_t ptr_simple[20], time_replies_t ptr_time[6],
    char *code, char *str)
{
    char *first_arg = get_args(str, 1);
    char *second_arg = get_args(str, 2);
    char *third_arg = get_args(str, 3);
    char *fourth_arg = get_args(str, 4);
    char *fifth_arg = get_args(str, 5);

    for (int i = 0; i < 20; i++)
        if (strncmp(ptr_simple[i].reply_code, code, 3) == 0) {
            ptr_simple[i].ptr(first_arg, second_arg, third_arg, fourth_arg);
            break;
        }
    for (int y = 0; y < 6; y++)
        if (strncmp(ptr_time[y].reply_code, code, 3) == 0) {
            ptr_time[y].ptr(first_arg, second_arg, time(NULL), fourth_arg,
                fifth_arg);
            break;
        }
    free(first_arg);
    free(second_arg);
    free_content(third_arg, fourth_arg, fifth_arg);
}

void pointer_function(char *str)
{
    char *code = NULL;
    simple_replies_t ptr_simple[20] = {{"101", code_101}, {"102", code_102},
        {"103", code_103}, {"104", code_104}, {"105", code_105},
        {"106", code_106}, {"109", code_109}, {"110", code_110},
        {"114", code_114}, {"115", code_115}, {"116", code_116},
        {"117", code_117}, {"119", code_119}, {"120", code_120},
        {"122", code_122}, {"123", code_123}, {"126", code_126},
        {"127", code_127}, {"128", code_128}, {"129", code_129}};
    time_replies_t ptr_time[6] = {{"107", code_107}, {"111", code_111},
        {"112", code_112}, {"121", code_121}, {"124", code_124},
        {"125", code_125}};

    code = get_args(str, 0);
    find_function(ptr_simple, ptr_time, code, str);
    others_commands(code, str);
    free(code);
}
