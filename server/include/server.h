/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** server
*/

#ifndef SERVER_H_
#define SERVER_H_

#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <uuid/uuid.h>
#include <signal.h>
#include "teams.h"

#define MAX_CLIENT 10
#define READING 0
#define WRITING 1
#define DEFAULT_NAME_LENGTH 32
#define DEFAULT_DESCRIPTION_LENGTH 255
#define DEFAULT_BODY_LENGTH 512

volatile bool keepRunning;

typedef struct messages_s {

    char *client_id;
    char **message;

}messages_t;

typedef struct clients_s {

    int fd_client;
    char user_id[37];
    char user_name[DEFAULT_NAME_LENGTH];
    bool logged;
    bool active;
    messages_t *conversation;
    char **use_state;

}clients_t;

typedef struct server_s {

    struct sockaddr_in inf;
    int nb_teams;
    int port;
    int fd_server;
    int nb_clients;
    char *command;
    FILE *fp;
    fd_set set[2];
    clients_t *clients;
    team_t *teams;
    char *a;

}server_t;

typedef struct cmds_s {

    char *command;
    void (*ptr)(server_t *, int, int);

}cmds_t;

void help(int, char **);
void error_handling(int, char **);
void start_server(char **);
void reading(server_t *);
void exec_commands(server_t *, int, int);
char *generate_id(void);
void new_client_struct(server_t *, int);
void remove_client(server_t *, int, int);
void login_user(server_t *, int, int);
void users_list(server_t *, int, int);
void send_messages(server_t *, int, int);
bool uuid_exit(server_t *, char *);
int uuid_index(server_t *, char *);
char *parse_args(server_t *, int);
void user(server_t *, int, int);
void fill_messages(server_t *, int, char *, char *);

//In user_messages.c
char *get_command_id(server_t *);
void print_messages(server_t *, int, char *, int);
bool does_id_exist(server_t *, int, int);
void client_mess(server_t *, int, int);

//In exec_command.c
void control_c(int __attribute__((unused)) contrl);
void list(server_t *, int, int);
void info(server_t *, int, int);

//In teams_handling.c
void create(server_t *, int, int);
void init_next_team(server_t *, int);
void use(server_t *, int, int);
void create_new_comment(server_t *, int, char *);
void comment_error(server_t *, char *, char *, int);

//In channel_handling.c
void create_new_channel(server_t *, int, char *, char *);
void init_next_channel(server_t *, int, int);

//In thread_handling.c
void create_new_thread(server_t *, int, char *, char *);
void init_next_thread(server_t *, int, int, int);

//In unsubscribe.c
void unsubscribe(server_t *, int, int);
void subscribed(server_t *, int, int);
void subscribe(server_t *, int, int);

#endif /* !SERVER_H_ */
