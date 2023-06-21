/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:57:24 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/21 11:51:08 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + nptr[i] - 48;
		i++;
	}
	return (res * sign);
}

int	is_number(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(char **cmd)
{
	write (1, "exit\n", 6);
	if (!cmd[0])
		return (0);
	if (is_number(cmd[0]) == 1)
		return (write(2, "bash: exit numeric argument required\n", 38), 2);
	if (ft_strslen(cmd) > 1)
		return (write(2, "bash: exit: too many arguments\n", 32), 1);
	else
		return (ft_atoi(cmd[0]));
	return (0);
}

void	exec_exit(char **cmd)
{
	int	test;

	test = ft_exit(cmd);
	if (test == 2)
		ft_main_exit(2);
	if (test == 1)
		g_shell->exit_value = 1;
	else
		ft_main_exit(test);
}
