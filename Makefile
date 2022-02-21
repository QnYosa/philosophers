NAME = philo

SRCS	= main.c parsing.c parsing_utils.c errors.c \
		init_struct.c display.c banquet.c time.c leaks.c \
		check_death.c \

OBJS	= ${SRCS:.c=.o}

CFLAGS	= -Wall -Werror -Wextra -g -pthread #-O3 -Wall -Werror -Wextra -g -pthread #-fsanitize=thread

CC		= gcc

RM		= rm -f

all:	$(NAME)

$(NAME):	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME} -lpthread

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o} 

clean:
		${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:		fclean all

.PHONY:		all clean fclean re bonus