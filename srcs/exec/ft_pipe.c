/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:23:37 by djanusz           #+#    #+#             */
/*   Updated: 2023/06/13 18:38:44 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

int	ft_cmdslen(char ***cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
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
		exec_buildin(cmd, 1);
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
	int		res;

	pipeline.i = 0;
	pipeline.prev_pipe = -1;
	pipeline.nbcmd = ft_cmdslen(cmds);
	pipeline.pid = malloc(sizeof(int) * (pipeline.nbcmd - 1));
	while (pipeline.i < pipeline.nbcmd)
	{
		if (pipe(pipeline.fd) == -1)
			return (-1);
		pipeline.pid[pipeline.i] = fork();
		if (pipeline.pid[pipeline.i] == 0)
			ft_pipe_child(&pipeline, cmds[pipeline.i], envp);
		ft_pipe_parent(&pipeline, cmds[pipeline.i]);
		pipeline.i++;
	}
	close(pipeline.prev_pipe);
	pipeline.i = 0;
	while (pipeline.i < pipeline.nbcmd)
		waitpid(pipeline.pid[pipeline.i++], &res, 0);
	free(pipeline.pid);
	return (WEXITSTATUS(res));
}
