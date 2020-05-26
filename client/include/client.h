/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** client
*/

#ifndef CLIENT_H_
#define CLIENT_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <signal.h>
#include "logging_client.h"

#define DEFAULT_NAME_LENGTH 32
#define DEFAULT_DESCRIPTION_LENGTH 255
#define DEFAULT_BODY_LENGTH 512
#define READING 0
#define WRITING 1

volatile bool oops;

typedef struct simple_replies_s {

    char *reply_code;
    void (*ptr)(char const *, char const *, char const *, char const *);

}simple_replies_t;

typedef struct time_replies_s {

    char *reply_code;
    void (*ptr)(char const *, char const *, time_t, char const *, char const *);

}time_replies_t;

void help(int, char **);
void error_handling(int, char **);
int client_side(char **);
void control_c(int __attribute__((unused)));
void terminal_killed(int __attribute__((unused)));
void pointer_function(char *);
char *get_args(char *command, int nb);

// code functions

void code_101(char const *, char const *, char const *, char const *);
void code_102(char const *, char const *, char const *, char const *);
void code_103(char const *, char const *, char const *, char const *);
void code_104(char const *, char const *, char const *, char const *);
void code_105(char const *, char const *, char const *, char const *);
void code_106(char const *, char const *, char const *, char const *);
void code_107(char const *, char const *, time_t ,char const *, char const *);
void code_108(char const *, char const *, int);
void code_109(char const *, char const *, char const *, char const *);
void code_110(char const *, char const *, char const *, char const *);
void code_111(char const *, char const *, time_t, char const *, char const *);
void code_112(char const *, char const *, time_t, char const *, char const *);
void code_113(char const *, char const *, time_t, char const *, char const *);
void code_114(char const *, char const *, char const *, char const *);
void code_115(char const *, char const *, char const *, char const *);
void code_116(char const *, char const *, char const *, char const *);
void code_117(char const *, char const *, char const *, char const *);
void code_118(char const *, char const *, int);
void code_119(char const *, char const *, char const *, char const *);
void code_120(char const *, char const *, char const *, char const *);
void code_121(char const *, char const *, time_t, char const *, char const *);
void code_122(char const *, char const *, char const *, char const *);
void code_123(char const *, char const *, char const *, char const *);
void code_124(char const *, char const *, time_t, char const *, char const *);
void code_125(char const *, char const *, time_t, char const *, char const *);
void code_126(char const *, char const *, char const *, char const *);
void code_127(char const *, char const *, char const *, char const *);
void code_128(char const *, char const *, char const *, char const *);
void code_129(char const *, char const *, char const *, char const *);

#endif /* !CLIENT_H_ */
