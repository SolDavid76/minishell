/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:52:44 by djanusz           #+#    #+#             */
/*   Updated: 2023/06/20 12:35:33 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

void	ft_exec(char ***cmds, char **envp)
{
	signal(SIGINT, SIG_IGN);
	g_shell->here_docs = here_doc(cmds);
	g_shell->exit_value = 0;
	if (ft_cmdslen(cmds) && !is_buildin(cmds[0][0]))
		ft_pipe(cmds, envp);
	else
		exec_buildin(cmds[0], 0);
}
