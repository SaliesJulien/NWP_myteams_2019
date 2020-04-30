/*
** EPITECH PROJECT, 2020
** generate random ID
** File description:
** myteams
*/

#include "server.h"

char *generate_id(void)
{
    uuid_t uid;
    char *uid_str = malloc(sizeof(char) * 37);

    uuid_generate(uid);
    uuid_unparse_lower(uid, uid_str);
    return (uid_str);
}