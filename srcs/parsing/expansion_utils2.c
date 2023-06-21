/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:03:01 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/21 12:10:03 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

char	*assign_variable(char *envp, int i)
{
	int		tmp;
	char	*res;

	tmp = i;
	while (envp[i])
		i++;
	res = (char *)malloc(sizeof(char) * (i - tmp + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (envp[tmp])
	{
		res[i] = envp[tmp];
		i++;
		tmp++;
	}
	res[i] = 0;
	return (res);
}

char	*check_variable_aux(char **envp, char *str, int i, char *tmp)
{
	int	j;

	j = 0;
	while (envp[j])
	{
		if (ft_strncmp(str, envp[j], i) == 0 && envp[j][i] == '=')
			tmp = assign_variable(envp[j], i + 1);
		j++;
	}
	if (str[i] && str[i] == '?')
		tmp = ft_strjoin_char(tmp, '?');
	return (tmp);
}

char	*check_variable(char *str, char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (str[i] == '?')
	{
		tmp = ft_itoa(g_shell->exit_value);
		return (tmp);
	}
	if (!is_alpha(str[i]))
		return (NULL);
	while (is_valid_variable(str[i]))
		i++;
	tmp = check_variable_aux(envp, str, i, tmp);
	if (tmp)
		return (tmp);
	return (NULL);
}

int	need_expand(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] && str[i + 1] == '?')
				return (2);
			return (1);
		}
		i++;
	}
	return (0);
}

char	*expand_with_cote(char *str, char c)
{
	int		i;
	int		tmp;
	char	*res;

	i = 1;
	while (str[i] && str[i] != c)
		i++;
	tmp = i;
	res = (char *)malloc(sizeof(char) * i + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i > tmp)
	{
		res[i] = str[i + 1];
		i++;
	}
	res[i] = 0;
	return (res);
}
