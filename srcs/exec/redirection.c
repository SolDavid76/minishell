/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:23:46 by djanusz           #+#    #+#             */
/*   Updated: 2023/06/14 15:48:23 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

void	ft_delete_redirection(char **cmd, int x)
{
	int		i;

	i = x + 2;
	free(cmd[x]);
	free(cmd[x + 1]);
	while (cmd[i])
		cmd[x++] = cmd[i++];
	cmd[i - 1] = NULL;
	cmd[i - 2] = NULL;
}

int	ft_redirection_aux(char **cmd, int i)
{
	int	fd;

	fd = 0;
	if (!ft_strcmp(cmd[i], ">"))
		fd = open(cmd[i + 1], O_CREAT + O_WRONLY + O_TRUNC, 0666);
	else if (!ft_strcmp(cmd[i], ">>"))
		fd = open(cmd[i + 1], O_CREAT + O_WRONLY + O_APPEND, 0666);
	else if (!ft_strcmp(cmd[i], "<"))
		fd = open(cmd[i + 1], O_RDONLY);
	if (fd == -1)
	{
		g_shell->exit_value = 1;
		write(2, "Permission denied: ", 20);
		write(2, cmd[i + 1], ft_strlen(cmd[i + 1]));
		write(2, "\n", 1);
	}
	return (fd);
}

void	ft_redirection(char **cmd)
{
	int	fd;
	int	i;

	i = 0;
	while (cmd[i])
	{
		fd = ft_redirection_aux(cmd, i);
		if (!ft_strcmp(cmd[i], ">") || !ft_strcmp(cmd[i], ">>"))
			dup2(fd, 1);
		else if (!ft_strcmp(cmd[i], "<"))
			dup2(fd, 0);
		if (fd)
		{
			if (fd != -1)
				close(fd);
			ft_delete_redirection(cmd, i);
		}
		else
			i++;
	}
}
