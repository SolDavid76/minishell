/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:33:30 by djanusz           #+#    #+#             */
/*   Updated: 2023/06/19 14:43:12 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

void	handler(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		g_shell->exit_value = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handler_exec(int signal)
{
	close(1);
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		ft_main_exit(130);
	}
	if (signal == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 20);
		ft_main_exit(131);
	}
}
