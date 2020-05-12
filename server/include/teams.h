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
#define DEFAULT_BODY_LENGTH 512

typedef struct thread_s {

    char thread_title[DEFAULT_NAME_LENGTH];
    char thread_content[DEFAULT_BODY_LENGTH];
    char thread_id[37];
    char **comment;

}thread_t;

typedef struct channel_s {

    char channel_name[DEFAULT_NAME_LENGTH];
    char channel_desc[DEFAULT_DESCRIPTION_LENGTH];
    char channel_id[37];
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