/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:57:24 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/26 10:42:16 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	sign;

	if (!nptr)
		return (0);
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

char	*ft_exit(char **cmd)
{
	write (1, "exit\n", 6);
	if (!cmd[0])
		ft_main_exit(g_shell->old_exit_value);
	if (is_number(cmd[0]) == 1)
		return (write(2, "exit: numeric argument required\n", 33), "a");
	if (ft_strslen(cmd) > 1)
		return (write(2, "exit: too many arguments\n", 26), "b");
	else
		return ((cmd[0]));
	return (0);
}

void	exec_exit(char **cmd)
{
	char	*test;

	test = ft_exit(cmd);
	if (ft_strcmp(test, "a") == 0)
		ft_main_exit(2);
	if (ft_strcmp(test, "b") == 0)
		g_shell->exit_value = 1;
	else
		ft_main_exit(ft_atoi(test));
}
