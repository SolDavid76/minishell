/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:33:30 by djanusz           #+#    #+#             */
/*   Updated: 2023/06/15 18:48:57 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

void	handler(int signal, siginfo_t *info, void* context)
{
	(void)info;
	(void)context;
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 1);
		rl_redisplay();
		g_shell->exit_value = 130;
		minishell();
	}
}

void	handler_child(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		ft_main_exit(131);
	}
	if (signal == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 20);
		ft_main_exit(131);
	}
}

void	signals_init(struct sigaction *data)
{
	sigemptyset(&data->sa_mask);
	data->sa_flags = SA_SIGINFO;
	data->sa_sigaction = handler;
	sigaction(SIGINT, data, 0);
	sigaction(SIGQUIT, data, 0);
}
