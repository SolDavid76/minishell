/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:22:43 by djanusz           #+#    #+#             */
/*   Updated: 2023/06/13 18:42:25 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_pipe
{
	int	prev_pipe;
	int	fd[2];
	int	nbcmd;
	int	*pid;
	int	i;
}	t_pipe;

/* lst.c */
t_list	*ft_lstnew(char *content);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lst_free(t_list	*lst);

/* ft_pipe.c */
int		ft_cmdslen(char ***cmds);
void	ft_pipe_child(t_pipe *pipeline, char **cmd, char **envp);
void	ft_pipe_parent(t_pipe *pipeline, char **cmd);
int		ft_pipe(char ***cmds, char **envp);

/* redirection.c */
void	ft_delete_redirection(char **cmd, int x);
int		ft_redirection_aux(t_pipe *pipeline, char **cmd, int i);
void	ft_redirection(t_pipe *pipeline, char **cmd);

/* here_doc.c */
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
void	*free_tab(char **ptr);
void	*free_tab_tab(char ***ptr);

/* builtins.c */
int		is_buildin(char *cmd);
int		exec_buildin(char **cmd, int mod);
void	echo(char **cmd);
// void	cd(char **cmd);
// void	pwd(char **cmd);
// void	unset(t_shell *shell, char *key);
// void	export(t_shell *shell, char *key);
// void	env(t_shell *shell);
// void	ft_exit(char **cmd);

/* shell.c */
int		is_in_variable(char c);
char	*ft_env_sub(char *key, char **envp);

/* exec.c */
void	ft_exec(char ***cmds, char **envp);

#endif
