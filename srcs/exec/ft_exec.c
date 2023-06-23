/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:52:44 by djanusz           #+#    #+#             */
/*   Updated: 2023/06/23 18:02:59 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

void	ft_exec(char ***cmds, char **envp)
{
	signal(SIGINT, SIG_IGN);
	g_shell->here_docs = here_doc(cmds);
	g_shell->old_exit_value = g_shell->exit_value;
	g_shell->exit_value = 0;
	if (!is_buildin(cmds[0][0]) || ft_cmdslen(cmds) != 1)
		ft_pipe(cmds, envp);
	else
	{
		ft_redirection(cmds[0]);
		if (!g_shell->exit_value)
			exec_buildin(cmds[0], 0);
	}
}
