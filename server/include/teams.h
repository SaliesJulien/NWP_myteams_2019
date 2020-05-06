/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** teams
*/

#ifndef TEAMS_H_
#define TEAMS_H_

#include "server.h"

typedef struct channel_s {

    char *channel_id;
    char **messages;

}channel_t;

typedef struct team_s {

    char *team_name;
    char *team_desc;
    char *team_id;
    channel_t *channel;

}team_t;

typedef enum team_statement_s {
    UNDEFINED,
    TEAM,
    CHANNEL,
    THREAD,
    COMMENT,
}team_statement_t;

#endif /* !TEAMS_H_ */