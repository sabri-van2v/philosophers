SRC = 	philo.c parsing.c utils.c \
		execute.c monitoring.c \
		routine.c print.c

SRCS = 	${addprefix srcs/, ${SRC}}

OBJ = 	${addprefix binaries/, ${SRC}}

OBJS = 	${OBJ:%.c=%.o}

NAME = 	philo

MAKEBIN = @mkdir -p binaries/

MAKEFLAGS += --no-print-directory 

CC 	= 	cc

RM 	= 	rm -f

CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = includes/

HEADER = includes/philo.h

binaries/%.o: srcs/%.c ${HEADER} | binaries
	${CC} ${CFLAGS} -c $< -o $@ ${addprefix -I, ${INCLUDES}}

${NAME}: ${OBJS}
	${CC} -o ${NAME} ${OBJS}

all: ${NAME}

binaries:
	${MAKEBIN}

clean:
	 ${RM} -r binaries

fclean: clean
	 ${RM} ${NAME}

re: fclean all

.PHONY:	all bonus clean fclean re