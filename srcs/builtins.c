#include "minishell.h"

int	isbuildin(char **cmd)
{
	if (ft_strcmp(cmd[0], "echo"))
		return (echo(cmd + 1, ft_strcmp(cmd[1], "-n")), 1);
	if (ft_strcmp(cmd[0], "cd"))
		return (1);
	if (ft_strcmp(cmd[0], "pwd"))
		return (1);
	if (ft_strcmp(cmd[0], "export"))
		return (1);
	if (ft_strcmp(cmd[0], "unset"))
		return (1);
	if (ft_strcmp(cmd[0], "env"))
		return (1);
	if (ft_strcmp(cmd[0], "exit"))
		return (1);
	return (0);
}

void	echo(char **cmd, int fd)
{
	int	option;
	int	i;

	option = ft_strcmp(cmd[0], "-n");
	i = option;
	while (cmd[i])
	{
		write(fd, cmd[i], ft_strlen(cmd[i]));
		i++;
	}
	if (!option)
		write(fd, "\n", 1);
}

void	pwd(char **cmd)
{
	int		size;
	char	*buf;

	if (cmd[1] != NULL)
	{
		write(2, "pwd: too many arguments\n", 24);
		return ;
	}
	size = 1;
	buf = NULL;
	while (!buf)
		buf = getcwd(buf, size++);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
}

void	unset(t_shell *shell, char *key)
{
	t_dict	*tmp;

	tmp = ft_dict_find(shell->env, key);
	if (tmp && tmp == shell->env)
		shell->env = shell->env->next;
	ft_dict_del(tmp);
}

void	env(t_shell *shell)
{
	t_dict	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		write(1, tmp->key, ft_strlen(tmp->key));
		write(1, "=", 1);
		write(1, tmp->content, ft_strlen(tmp->content));
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}
