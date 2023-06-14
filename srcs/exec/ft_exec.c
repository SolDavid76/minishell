/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:52:44 by djanusz           #+#    #+#             */
/*   Updated: 2023/06/14 17:26:46 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

void	print_cmds(char ***cmds)
{
	int	i;
	int	j;

	i = 0;
	fprintf(stderr, "cmds = ");
	while (cmds[i])
	{
		j = 0;
		while (cmds[i][j])
		{
			fprintf(stderr, "%s ", cmds[i][j]);
			j++;
		}
		i++;
	}
	fprintf(stderr, "\n");
}

void	ft_exec(char ***cmds, char **envp)
{
	g_shell->here_docs = here_doc(cmds);
	if (ft_cmdslen(cmds) == 1 && is_buildin(cmds[0][0]))
		exec_buildin(cmds[0], 0);
	else
		ft_pipe(cmds, envp);
}
// pid = fork();
// if (pid == 0)
// 	here_doc(cmds);
// waitpid(pid, 0, 0);