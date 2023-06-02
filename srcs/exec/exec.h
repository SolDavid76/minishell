#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_dict
{
	char			*key;
	char			*content;
	struct s_list	*next;
}					t_dict;

typedef struct s_shell
{
	t_dict	*dict;
	char	**envp;
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

/* utils.c */
int		ft_strlen(char *str);
int		ft_tablen(char **tab);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);

/* lst.c */
t_list	*ft_lstnew(char *content);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lst_free(t_list	*lst);

/* ft_pipe.c */
void	ft_pipe_child(t_pipe *pipeline, char **cmd, char **envp);
void	ft_pipe_parent(t_pipe *pipeline, char **cmd);
int		ft_pipe(char ***cmds, char **envp);

/* redirection.c */
void	ft_delete_redirection(char **cmd, int x);
int		ft_redirection_aux(t_pipe *pipeline, char **cmd, int i);
void	ft_redirection(t_pipe *pipeline, char **cmd);

/* here_doc.c */
int		is_valid_variable(char c);
t_list	*here_doc_write(t_list *docs, t_list *input, char *eof, int fd);
t_list	*here_doc_open(t_list *docs, t_list *input, char *eof);
t_list	*here_doc_aux(t_list *docs, char **cmd, int x);
t_list	*here_doc(char ***cmds);

/* ft_itoa.c */
void	ft_putchar_fd(int fd, char c);
void	ft_putnbr_fd(int fd, int n);
int		intlen(long int x);
char	*ft_itoa(int x);

/* free.c */
void	free_tab(char **ptr);
void	free_tab_tab(char ***ptr);

/* builtins.c */
int		is_buildin(char *cmd);
void	exec_buildin(char **cmd);
void	echo(char **cmd);
// void	cd(char **cmd);
// void	pwd(char **cmd);
// void	unset(t_shell *shell, char *key);
// void	export(t_shell *shell, char *key);
// void	env(t_shell *shell);
// void	ft_exit(char **cmd);

/* shell.c */
void	ft_main_exit(int code);
t_shell	*get_shell(void);
char	**ft_envdup(char **envp);
char	*ft_env_sub(char *key);

#endif
