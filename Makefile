SRCS_DIR	= srcs/

SRC			= builtins.c \
			  dict.c \
			  dict_aux.c \
			  main.c \
			  utils.c \

SRCS		= $(addprefix $(SRCS_DIR), $(SRC))

OBJS_DIR	= objs/

OBJ			= ${SRC:.c=.o}

OBJS		= $(addprefix $(OBJS_DIR), $(OBJ))

NAME		= minishell

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

INCS		= -I ./includes/

READLINE	= -L /usr/local/lib -I /usr/local/include -lreadline

all:		${OBJS_DIR} ${NAME}

${OBJS_DIR}:
			mkdir ${OBJS_DIR}

${OBJS_DIR}%.o: ${SRCS_DIR}%.c
			${CC} ${CFLAGS} -c $< -o $@ ${INCS}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} ${READLINE} -o ${NAME}

clean:
			rm -rf ${OBJS_DIR}

fclean:		clean
			rm -f ${NAME}
			rm -f a.out

re:			fclean all

.PHONY:		all clean fclean re
