SRCS_DIR	= 	srcs/parsing/

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

SRCS_EX_DIR		= srcs/exec/

SRC_EX	=		builtins.c\
				free.c\
				ft_itoa.c\
				ft_pipe.c\
				here_doc.c\
				lst.c\
				redirection.c\
				shell.c\

SRCS_UTI_DIR	=	srcs/

SRC_UTI			=	main.c\
					utils.c\


SRCS =$(addprefix $(SRCS_DIR), $(SRC))\
	$(addprefix $(SRCS_EX_DIR), $(SRC_EX))\
	$(addprefix $(SRCS_UTI_DIR), $(SRC_UTI))\

OBJS_DIR	=	obj/

OBJ 		= $(SRC:.c=.o)\
				$(SRC_EX:.c=.o)\
				$(SRC_UTI:.c=.o)\


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

$(OBJS_DIR)%.o: $(SRCS_EX_DIR)%.c
	$(CC) $(FLAGS) -c $< -o $@ $(INCS)

$(OBJS_DIR)%.o: $(SRCS_UTI_DIR)%.c
	$(CC) $(FLAGS) -c $< -o $@ $(INCS)


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