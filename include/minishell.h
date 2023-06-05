#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing.h"
# include "exec.h"

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_shell
{
	t_dict	*dict;
	char	**envp;
	char	***cmds;
}			t_shell;

/* main.c */
void	ft_main_exit(int code);
t_shell	*get_shell(void);
char	**ft_envdup(char **envp);
char	***big_join(t_list *lst);

/* utils.c */
int		ft_strlen(char *str);
int		ft_tablen(char **tab);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);

#endif