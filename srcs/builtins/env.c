/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:57:05 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/19 12:14:47 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

void env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		// printf("%s\n", envp[i]);
		write(1, envp[i], ft_strlen(envp[i]));
		i++;
	}
}