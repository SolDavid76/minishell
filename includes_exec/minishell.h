#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

//useless now
typedef struct s_dict
{
	char			*key;
	char			*content;
	struct s_dict	*prev;
	struct s_dict	*next;
}					t_dict;

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_shell
{
	t_dict	*env;
	char	***cmds;
}			t_shell;

typedef struct s_pipe
{
	int	prev_pipe;
	int	fd[2];
	int	nbcmd;
	int	pid;
	int	i;
}	t_pipe;

/* dict.c */
t_dict	*ft_dictnew(char *key, char *content);
int		ft_dictsize(t_dict *dict);
t_dict	*ft_dictlast(t_dict *dict);
void	ft_dictadd_back(t_dict **dict, t_dict *new);
t_dict	*ft_dict_find(t_dict *dict, char *key);
t_dict	*ft_dict_find(t_dict *dict, char *key);
void	ft_dict_del(t_dict	*dict);
void	ft_dict_free(t_dict	*dict);

/* lst.c */
t_list	*ft_lstnew(char *content);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lst_free(t_list	*lst);

/* utils.c */
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_strchr(char *str, char c);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_char(char *str, char c);
char	*gnl(int fd, char *eof);
t_dict	*dicting(char **env);
void	*free_map(char **map);
char	**maping(t_dict *dict);

/* builtins.c */
void	echo(char **cmd);
void	cd(char **cmd);
void	pwd(char **cmd);
void	unset(t_shell *shell, char *key);
void	export(t_shell *shell, char *key);
void	env(t_shell *shell);
void	ft_exit(char **cmd);

/* main.c */
void	free_shell(t_shell *shell);
void	ft_main_exit(t_shell *shell, int code);
t_shell	*get_shell(void);
int		ft_pipe(char ***cmds, char **envp);

#endif
