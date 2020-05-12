/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** teams
*/

#ifndef TEAMS_H_
#define TEAMS_H_

#include "server.h"

#define DEFAULT_NAME_LENGTH 32
#define DEFAULT_DESCRIPTION_LENGTH 255

typedef struct thread_s {

    char *thread_title;
    char *thread_content;
    char *thread_id;
    char **comment;

}thread_t;

typedef struct channel_s {

    char *channel_name;
    char *channel_desc;
    char *channel_id;
    thread_t *thread;

}channel_t;

typedef struct team_s {

    char team_name[DEFAULT_NAME_LENGTH];
    char team_desc[DEFAULT_DESCRIPTION_LENGTH];
    char team_id[37];
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