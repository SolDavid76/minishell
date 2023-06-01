SRCS_DIR	= 	srcs_parsing/

SRC		=		acces.c\
				list.c\
				parameter_expansion.c\
				lexer_utils.c\
				remove_quote.c\
				parsing.c\
				split_pipe.c\
				split_redirect.c\
				pipe_utils.c\
				pipe_utils2.c\
				pipe_utils3.c\
				redi_utils.c\
				redi_utils2.c\
				expansion_utils.c\
				expansion_utils2.c\
				acces_split.c\
				substiution_utils.c\
				substitution_utils2.c\
				list2.c\




SRCS =$(addprefix $(SRCS_DIR), $(SRC))


OBJS_DIR	=	obj/

OBJ 		= $(SRC:.c=.o)

OBJS 		= $(addprefix $(OBJS_DIR), $(OBJ))

NAME 		= 	minishell

CC			= 	gcc

FLAGS		= 	-Wall -Wextra -Werror -g

INCS 		= 	-I ./include/

READLINE	= -L /usr/local/lib -I /usr/local/include -lreadline

RM = rm -f

all : ${OBJS_DIR} ${NAME}

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	${CC} ${FLAGS} -c $< -o $@ ${INCS}

$(OBJS_DIR):
	mkdir $(OBJS_DIR)


${NAME}: ${OBJS}
		${CC} ${FLAGS} ${OBJS} -o $(NAME) ${READLINE}

clean : 
	rm -rf ${OBJS_DIR}

fclean : clean
	${RM} ${NAME}

re :	fclean all

.PHONY : all clean fclean re             