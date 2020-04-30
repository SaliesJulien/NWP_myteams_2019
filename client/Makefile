##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## client
##

SRCS = ./src/

SRCCLIENT =	$(SRCS)main.c 					\
			$(SRCS)client.c 				\
			$(SRCS)arguments.c 				\

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I./include

BINARYNAME_CLIENT = ../myteams_client

OBJCLIENT = $(SRCCLIENT:.c=.o)

all: $(BINARYNAME_CLIENT)

$(BINARYNAME_CLIENT): $(OBJCLIENT)
	$(CC) -o $(BINARYNAME_CLIENT) $(OBJCLIENT) $(CFLAGS)

clean:
	$(RM) $(OBJCLIENT)

fclean: clean
	$(RM) $(BINARYNAME_CLIENT)

re: fclean all

debug:	CLIENTFLAGS += -g3
debug:	fclean all

.PHONY: all clean fclean re debug
