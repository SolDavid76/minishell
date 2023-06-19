/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:02:09 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/19 16:21:30 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int skip_newline(char **str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_strcmp("-n", str[i]) == 0))
		i++;
	return (i);
}
void	echo(char **cmd)
{
	int	option;
	int	i;

	option = !ft_strcmp(cmd[0], "-n");
	i = option;
	if (option)
		i = skip_newline(cmd);
	
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!option)
		write(1, "\n", 1);
}