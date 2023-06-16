/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:52:44 by djanusz           #+#    #+#             */
/*   Updated: 2023/06/16 15:07:22 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

void	ft_exec(char ***cmds, char **envp)
{
	g_shell->here_docs = here_doc(cmds);
	if (ft_cmdslen(cmds) == 1 && is_buildin(cmds[0][0]))
		exec_buildin(cmds[0], 0);
	else
		ft_pipe(cmds, envp);
}
