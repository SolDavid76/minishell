/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:52:44 by djanusz           #+#    #+#             */
/*   Updated: 2023/06/23 18:57:04 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

void	ft_exec(char ***cmds, char **envp)
{
	g_shell->old_exit_value = g_shell->exit_value;
	g_shell->exit_value = 0;
	signal(SIGINT, handler_here_doc);
	g_shell->here_docs = here_doc(cmds);
	signal(SIGINT, SIG_IGN);
	if (g_shell->exit_value == 130)
		return ;
	if (!is_buildin(cmds[0][0]) || ft_cmdslen(cmds) != 1)
		ft_pipe(cmds, envp);
	else
	{
		ft_redirection(cmds[0]);
		if (!g_shell->exit_value)
			exec_buildin(cmds[0], 0);
	}
}
