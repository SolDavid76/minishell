/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:52:44 by djanusz           #+#    #+#             */
/*   Updated: 2023/06/19 11:39:14 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

void	ft_exec(char ***cmds, char **envp)
{
	int	exec_pid;

	signal(SIGINT, SIG_IGN);
	g_shell->here_docs = here_doc(cmds);
	exec_pid = fork();
	if (exec_pid == 0)
	{
		signal(SIGINT, handler_exec);
		signal(SIGQUIT, handler_exec);
		if (ft_cmdslen(cmds) == 1 && is_buildin(cmds[0][0]))
			exec_buildin(cmds[0], 0);
		else
			ft_pipe(cmds, envp);
		ft_main_exit(g_shell->exit_value);
	}
	waitpid(exec_pid, 0, 0);
}
