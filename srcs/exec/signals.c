/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:33:30 by djanusz           #+#    #+#             */
/*   Updated: 2023/06/23 18:59:54 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

void	handler(int signal)
{
	if (signal == SIGINT)
	{
		g_shell->exit_value = 130;
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handler_here_doc(int signal)
{
	if (signal == SIGINT)
	{
		close(0);
		g_shell->exit_value = 130;
		write(2, "\n", 1);
	}
}

void	status_update(int status)
{
	if (WEXITSTATUS(status))
		g_shell->exit_value = WEXITSTATUS(status);
	else if (WTERMSIG(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			g_shell->exit_value = 130;
			write(1, "\n", 1);
		}
		if (WTERMSIG(status) == SIGQUIT)
		{
			g_shell->exit_value = 131;
			write(1, "Quit (core dumped)\n", 19);
		}
	}
}
