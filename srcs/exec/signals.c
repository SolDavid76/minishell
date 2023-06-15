/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:33:30 by djanusz           #+#    #+#             */
/*   Updated: 2023/06/15 15:40:13 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

void	handle(int signal)
{
	if (signal == SIGINT)
	{
		g_shell->exit_value = 130;
	}
	if (signal == SIGQUIT)
		g_shell->exit_value = 131;
}
