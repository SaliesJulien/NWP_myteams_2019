/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** server
*/

#ifndef SERVER_H_
#define SERVER_H_

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <dirent.h>
#include <uuid/uuid.h>

#define MAX_CLIENT 10
#define READING 0
#define WRITING 1
#define DEFAULT_NAME_LENGTH 32
#define DEFAULT_DESCRIPTION_LENGTH 255
#define DEFAULT_BODY_LENGTH 512

typedef struct clients_s {

    int fd_client;
    char *user_id;

}clients_t;

typedef struct server_s {

    struct sockaddr_in inf;
    int port;
    int fd_server;
    int nb_clients;
    char *command;
    fd_set set[2];
    clients_t *clients;

}server_t;

void help(int, char **);
void error_handling(int, char **);
void start_server(char **);
void reading(server_t *);
void exec_commands(server_t *, int, int);
char *generate_id(void);
void new_client_struct(server_t *server, int fd);

#endif /* !SERVER_H_ */
