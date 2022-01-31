#			NAME			#
NAME = 		philosphers

#			COMPILATOR		#
COMPILER = 	cc

#			VARIABLES		#
SRCS =	main.c 

INCLUDES 	= includes/philosophers.h

#			OBJECTS			#

OBJS	=	${SRCS:.c=.o}
OBJS	:= 	$(addprefix objs/,${OBJS})
DEP		= 	$(OBJS:.o=.d)

# 			FLAGS 		#

FLAGS	= 	-g -Wall -Werror -Wextra

#			RULES		#

all:		${NAME}

$(NAME):	${OBJS} ${INCLUDES}
			${COMPILER} ${FLAGS} -I includes ${OBJS} -O $(NAME)

-include $(DEP)

objs/%.o:		srcs/%.c
					@mkdir -p $(dir $@)
					@${COMPILER} -MMD ${FLAGS} -I includes -o $@ -c $<

norme:
				@norminette srcs/*
				@norminette includes/*

clean:
				rm -f ${OBJS}

fclean:
				rm -f ${OBJS}
				rm -f ${NAME}
				rm -rf objs

re:				fclean all

.PHONY:			all norme clean fclean re