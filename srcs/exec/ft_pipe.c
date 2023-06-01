#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

//return 1 if equal
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] == s2[i]);
}

void	echo(char **cmd)
{
	int	option;
	int	i;

	option = ft_strcmp(cmd[0], "-n");
	i = option;
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!option)
		write(1, "\n", 1);
}

int	is_buildin(char *cmd)
{
	if (ft_strcmp(cmd, "echo"))
		return (1);
	if (ft_strcmp(cmd, "cd"))
		return (1);
	if (ft_strcmp(cmd, "pwd"))
		return (1);
	if (ft_strcmp(cmd, "export"))
		return (1);
	if (ft_strcmp(cmd, "unset"))
		return (1);
	if (ft_strcmp(cmd, "env"))
		return (1);
	if (ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

// delete

int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

void	ft_putchar_fd(int fd, char c)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int fd, int n)
{
	unsigned int	x;

	if (n < 0)
	{
		x = -n;
		ft_putchar_fd(fd, '-');
	}
	else
		x = n;
	if (x > 9)
	{
		ft_putnbr_fd(fd, x / 10);
		x = x % 10;
	}
	ft_putchar_fd(fd, x + '0');
}

int	ft_nbrcmd(char ***cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

void	exec_buildin(char **cmd)
{
	if (ft_strcmp(cmd[0], "echo"))
		echo(cmd + 1);
	// else if (ft_strcmp(cmd[0], "cd"))
	// 	return (1);
	// else if (ft_strcmp(cmd[0], "pwd"))
	// 	return (1);
	// else if (ft_strcmp(cmd[0], "export"))
	// 	return (1);
	// else if (ft_strcmp(cmd[0], "unset"))
	// 	return (1);
	// else if (ft_strcmp(cmd[0], "env"))
	// 	return (1);
	// else if (ft_strcmp(cmd[0], "exit"))
	// 	return (1);
	exit(0);
}

int	ft_cmdlen(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

void	printcmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		write(2, cmd[i], ft_strlen(cmd[i]));
		write(2, " ", 1);
		i++;
	}
	write(2, "\n", 1);
}

	// free(cmd[x]);
	// free(cmd[x + 1]);
void	ft_delete_redirection(char **cmd, int x)
{
	int		i;

	i = x + 2;
	while (cmd[i])
		cmd[x++] = cmd[i++];
	cmd[i - 1] = NULL;
	cmd[i - 2] = NULL;
}

int	ft_redirection_aux(t_pipe *pipeline, char **cmd, int i)
{
	int	fd;

	fd = 0;
	if (ft_strcmp(cmd[i], ">"))
		fd = open(cmd[i + 1], O_CREAT + O_WRONLY, 0666);
	else if (ft_strcmp(cmd[i], ">>"))
		fd = open(cmd[i + 1], O_CREAT + O_WRONLY + O_APPEND, 0666);
	else if (ft_strcmp(cmd[i], "<"))
		fd = open(cmd[i + 1], O_RDONLY);
	if (fd == -1)
	{
		close(pipeline->fd[0]);
		close(pipeline->fd[1]);
		write(2, "Permission denied: ", 20);
		write(2, cmd[i + 1], ft_strlen(cmd[i + 1]));
		write(2, "\n", 1);
		exit(1);
	}
	return (fd);
}

void	ft_redirection(t_pipe *pipeline, char **cmd)
{
	int	fd;
	int	i;

	i = 0;
	while (cmd[i])
	{
		fd = ft_redirection_aux(pipeline, cmd, i);
		if (ft_strcmp(cmd[i], ">") || ft_strcmp(cmd[i], ">>"))
			dup2(fd, 1);
		else if (ft_strcmp(cmd[i], "<"))
			dup2(fd, 0);
		if (fd)
		{
			close(fd);
			ft_delete_redirection(cmd, i);
		}
		else
			i++;
	}
}

void	ft_pipe_child(t_pipe *pipeline, char **cmd, char **envp)
{
	if (pipeline->i != 0)
	{
		dup2(pipeline->prev_pipe, 0);
		close(pipeline->prev_pipe);
	}
	if (pipeline->i != pipeline->nbcmd - 1)
		dup2(pipeline->fd[1], 1);
	ft_redirection(pipeline, cmd);
	close(pipeline->fd[0]);
	close(pipeline->fd[1]);
	if (is_buildin(cmd[0]))
		exec_buildin(cmd);
	if (access(cmd[0], X_OK) == 0)
		execve(cmd[0], cmd, envp);
}

void	ft_pipe_parent(t_pipe *pipeline, char **cmd)
{
	if (access(cmd[0], X_OK) == -1 && !is_buildin(cmd[0]))
	{
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ": command not found\n", 20);
	}
	close(pipeline->fd[1]);
	if (pipeline->prev_pipe != -1)
		close(pipeline->prev_pipe);
	pipeline->prev_pipe = pipeline->fd[0];
}

//fd[1] == entre
//fd[0] == sortie
int	ft_pipe(char ***cmds, char **envp)
{
	t_pipe	pipeline;

	pipeline.i = 0;
	pipeline.prev_pipe = -1;
	pipeline.nbcmd = ft_nbrcmd(cmds);
	while (pipeline.i < pipeline.nbcmd)
	{
		if (pipe(pipeline.fd) == -1)
			return (-1);
		if (!access(cmds[pipeline.i][0], X_OK)
			|| is_buildin(cmds[pipeline.i][0]))
		{
			pipeline.pid = fork();
			if (pipeline.pid == 0)
				ft_pipe_child(&pipeline, cmds[pipeline.i], envp);
		}
		ft_pipe_parent(&pipeline, cmds[pipeline.i]);
		pipeline.i++;
	}
	close(pipeline.prev_pipe);
	waitpid(0, 0, 0);
	return (pipeline.i);
}

int	intlen(long int x)
{
	size_t	res;

	res = 1;
	if (x < 0)
	{
		x = -x;
		res++;
	}
	while (x > 9)
	{
		x /= 10;
		res++;
	}
	return (res);
}

char	*ft_itoa(int x)
{
	char		*res;
	int			start;
	int			len;
	long int	nb;

	nb = x;
	len = intlen(nb);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len--] = '\0';
	start = 0;
	if (nb < 0)
	{
		res[0] = '-';
		nb = -nb;
		start++;
	}
	while (len >= start)
	{
		res[len--] = ((nb % 10) + 48);
		nb /= 10;
	}
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!res)
		exit(1);
	i = 0;
	j = 0;
	if (s1)
		while (s1[i])
			res[j++] = s1[i++];
	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = '\0';
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (res);
}

char	*ft_strdup(char *str)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		exit(1);
	i = -1;
	while (str[++i])
		res[i] = str[i];
	res[i] = '\0';
	return (res);
}

int ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return (s1[i] == s2[i]);
}

char	*ft_env_sub(char **envp, char *key)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)))
			return (envp[i] + ft_strlen(key) + 1);
		i++;
	}
	return (NULL);
}

t_list	*here_doc_open(t_list *docs, t_list *input, char *eof)
{
	char	*str;
	int		fd;
	int		i;

	i = 0;
	fd = -1;
	str = NULL;
	while (fd == -1)
	{
		if (str)
			free(str);
		str = ft_strjoin(ft_strdup(".here_doc"), ft_itoa(i++));
		fd = open(str, O_CREAT + O_EXCL + O_WRONLY, 0666);
	}
	ft_lstadd_back(&docs, ft_lstnew(str));
	while (input && !ft_strcmp(input->content, eof))
	{
		str = ft_env_sub(input->content)
		write(fd, str, ft_strlen(str));
		if (str)
			write(fd, "\n", 1);
		input = input->next;
	}
	close(fd);
	return (docs);
}

t_list	*here_doc_aux(t_list *docs, char **cmd, int x)
{
	t_list	*input;
	int		i;

	i = 0;
	input = NULL;
	ft_lstadd_back(&input, ft_lstnew(readline(">")));
	while (!ft_strcmp(ft_lstlast(input)->content, cmd[x + 1])
		&& ft_lstlast(input)->content)
	{
		ft_lstadd_back(&input, ft_lstnew(readline(">")));
		i++;
	}
	if (!ft_lstlast(input)->content)
	{
		write(2, "warning : here-document at line ", 33);
		ft_putnbr_fd(2, i);
		write(2, " delimited by end-of-file (wanted `", 36);
		write(2, cmd[x + 1], ft_strlen(cmd[x + 1]));
		write(2, "')\n", 3);
	}
	docs = here_doc_open(docs, input, cmd[x + 1]);
	ft_lst_free(input);
	cmd[x] = "<";
	cmd[x + 1] = ft_lstlast(docs)->content;
	return (docs);
}

t_list	*here_doc(char ***cmds)
{
	t_list	*docs;
	int		i;
	int		j;

	i = 0;
	docs = NULL;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i][j])
		{
			if (ft_strcmp(cmds[i][j], "<<"))
				docs = here_doc_aux(docs, cmds[i], j);
			j++;
		}
		i++;
	}
	return (docs);
}

int	main(int ac, char **av, char **envp)
{
	char	*echo[10] = {"echo", "Hello 42.", ">>", "test", ">>", "llll", NULL};
	char	*cat[5] = {"/usr/bin/cat", "<<", "EOF"};
	char	*ls[5] = {"/usr/bin/ls", "srcs", NULL};
	char	*trash[2] = {"blablabla", NULL};
	char	*wc[3] = {"/bin/wc", "-l", NULL};
	char	*grep[3] = {"/usr/bin/grep", "dict", NULL};
	char	*touch[3] = {"/usr/bin/touch", "lol", NULL};
	char	*rm[4] = {"/usr/bin/rm", "-f", "lol", NULL};
	char	**cmds[6] = {ls, cat, wc, NULL};

	t_list *lst = here_doc(cmds);
	t_list *tmp = lst;
	ft_pipe(cmds, envp);
	while (tmp)
	{
		unlink(tmp->content);
		tmp = tmp->next;
	}
	ft_lst_free(lst);
	(void)ac;
	(void)av;
	(void)cat;
	(void)echo;
	(void)envp;
	(void)ls;
	(void)trash;
	(void)wc;
	(void)grep;
	(void)touch;
	(void)rm;
	(void)cmds;
}
