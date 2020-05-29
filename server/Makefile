##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## server
##

SRCS = ./src/

SRCSERVER =	$(SRCS)main.c 					\
			$(SRCS)arguments.c 				\
			$(SRCS)server.c 				\
			$(SRCS)read_client.c 			\
			$(SRCS)exec_commands.c 			\
			$(SRCS)new_client.c 			\
			$(SRCS)generate_id.c 			\
			$(SRCS)/send/send.c 					\
			$(SRCS)/send/conversation_exist.c 		\
			$(SRCS)login.c					\
			$(SRCS)users.c					\
			$(SRCS)tools.c					\
			$(SRCS)user_messages.c			\
			$(SRCS)user.c					\
			$(SRCS)teams_handling.c  		\
			$(SRCS)thread_handling.c 		\
			$(SRCS)channel_handling.c 		\
			$(SRCS)comment_handling.c 		\
			$(SRCS)/use_handling/use_handling.c 			\
			$(SRCS)/use_handling/use_without_id.c 			\
			$(SRCS)/use_handling/use_one_id.c 				\
			$(SRCS)/use_handling/use_two_id.c 				\
			$(SRCS)/use_handling/use_three_id.c 			\
			$(SRCS)/use_handling/unknown_use_id.c 			\
			$(SRCS)list.c 					\
			$(SRCS)info.c 					\
			$(SRCS)unsubscribe.c 			\
			$(SRCS)subscribe.c 				\
			$(SRCS)subscribed.c 			\
			$(SRCS)save.c 					\
			$(SRCS)read.c 					\
			$(SRCS)parse_content.c 			\


CC = gcc

CFLAGS = -Wall -Werror -Wextra -I./include -I../libs/myteams -L../libs/myteams -lmyteams -luuid

BINARYNAME_SERVER = ../myteams_server

OBJSERVER = $(SRCSERVER:.c=.o)

all: $(BINARYNAME_SERVER)

$(BINARYNAME_SERVER): $(OBJSERVER)
	$(CC) -o $(BINARYNAME_SERVER) $(OBJSERVER) $(CFLAGS)

clean:
	$(RM) $(OBJSERVER)

fclean: clean
	$(RM) $(BINARYNAME_SERVER)

re: fclean all

debug:	SERVERFLAGS += -g3
debug:	fclean all

.PHONY: all clean fclean re debug
