##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Teams
##

SRCFOLDER = ./src/

SRCSERVER =	$(SRCFOLDER)server/main.c \
			$(SRCFOLDER)server/server.c \

SRCCLIENT =	$(SRCFOLDER)client/main.c \
			$(SRCFOLDER)client/client.c \

CXX = gcc
CFLAGS = -Wall -Werror -Wextra -I./include

BINARYNAMESERVER = myteams_server

BINARYNAMECLIENT = myteams_client

OBJSERVER = $(SRCSERVER:.c=.o)

OBJCLIENT = $(SRCCLIENT:.c=.o)

all: $(BINARYNAMESERVER) $(BINARYNAMECLIENT)

$(BINARYNAMESERVER) $(BINARYNAMECLIENT): $(OBJSERVER) $(OBJCLIENT)
	$(CXX) -o $(BINARYNAMESERVER) $(OBJSERVER) $(CFLAGS)
	$(CXX) -o $(BINARYNAMECLIENT) $(OBJCLIENT) $(CFLAGS)

clean:
	$(RM) $(OBJSERVER)
	$(RM) $(OBJCLIENT)

fclean: clean
	$(RM) $(BINARYNAMESERVER)
	$(RM) $(BINARYNAMECLIENT)

re: fclean all

.PHONY: all clean fclean re

debug:	CFLAGS += -g3
debug:	fclean all