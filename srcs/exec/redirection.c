#include "minishell.h"

void	ft_delete_redirection(char **cmd, int x)
{
	int		i;

	i = x + 2;
	// free(cmd[x]);
	// free(cmd[x + 1]);
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
