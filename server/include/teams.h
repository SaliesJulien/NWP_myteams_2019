/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** teams
*/

#ifndef TEAMS_H_
#define TEAMS_H_

#include "server.h"

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

    char *team_name;
    char *team_desc;
    char *team_id;
    channel_t *channel;

}team_t;

#endif /* !TEAMS_H_ */