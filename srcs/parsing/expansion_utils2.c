/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:03:01 by ennollet          #+#    #+#             */
/*   Updated: 2023/05/31 10:08:45 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*check_variable(char *str, char **envp)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (!is_alpha(str[i]))
		return (NULL);
	while (is_valid_variable(str[i]))
		i++;
	j = 0;
	while (envp[j])
	{
		if (ft_strncmp(str, envp[j], i) == 0 && envp[j][i] == '=')
			tmp = assign_variable(envp[j], i + 1);
		j++;
	}
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
			return (1);
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
