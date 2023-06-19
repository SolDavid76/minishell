/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:52:44 by djanusz           #+#    #+#             */
/*   Updated: 2023/06/19 14:44:59 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

void	ft_exec(char ***cmds, char **envp)
{
	int	pid;

	g_shell->here_docs = here_doc(cmds);
	signal(SIGINT, SIG_IGN);
	if (ft_cmdslen(cmds) && !is_buildin(cmds[0][0]))
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, handler_exec);
			signal(SIGQUIT, handler_exec);
			ft_pipe(cmds, envp);
		}
		waitpid(pid, 0, 0);
	}
	else
		exec_buildin(cmds[0], 0);
}
