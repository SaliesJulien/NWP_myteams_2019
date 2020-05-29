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
			$(SRCS)catch_sigint.c 			\
			$(SRCS)function_handling.c 		\
			$(SRCS)handle_commands.c 		\
			$(SRCS)code_101_105.c 			\
			$(SRCS)code_106_110.c 			\
			$(SRCS)code_111_115.c 			\
			$(SRCS)code_116_120.c 			\
			$(SRCS)code_121_125.c 			\
			$(SRCS)code_126_129.c 			\

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I./include -I../libs/myteams -L../libs/myteams -lmyteams

BINARYNAME_CLIENT = ../myteams_cli

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
