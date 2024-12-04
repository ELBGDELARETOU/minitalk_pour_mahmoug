NAME = client

SRCS = client.c server.c utils.client

OBJS = ${SRCS:.c=.o}

CC = cc -Wall -Werror -Wextra

all: client server

client: client.c
		${CC} -o client client.c utils.c

server: server.c
		${CC} -o server server.c utils.c

clean:
		rm -rf ${OBJS}

fclean:
		rm -rf client server ${OBJS}

re: fclean all