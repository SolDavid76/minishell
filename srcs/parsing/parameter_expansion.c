/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:41:31 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/23 19:32:28 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_expand_flag(int flag, char content)
{
	if (content == '\'' && flag == 0)
			flag = 1;
	else if (content == '\'' && flag == 1)
		flag = 0;
	if (content == '"' && flag == 0)
		flag = 2;
	else if (content == '"' && flag == 2)
		flag = 0;
	return (flag);
}

int	dollar_test(char *str)
{
	int	i;

	i = 0;
	if (str[i + 1] && (str[i + 1] != 0 && (str[i + 1] != '$')))
		return (0);
	return (1);
}

char	*new_expand_aux(char *content, char *res, int flag, char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (content[i])
	{
		if (content[i] == '$')
		{
			if (flag != 1 && dollar_test(content + i) == 0)
			{
				tmp = check_variable(content + i + 1, envp);
				res = ft_strjoin(res, tmp);
				i++;
				while (is_valid_variable(content[i]))
					i++;
				if (content[i] == '?')
					i++;
			}
		}
		flag = new_expand_flag(flag, content[i]);
		if (content[i] && (flag == 1 || dollar_test(content + i) == 1))
			res = ft_strjoin_char(res, content[i++]);
	}
	return (res);
}

char	*new_expand(char *content, char **envp)
{
	char	*res;
	int		flag;

	res = NULL;
	flag = 0;
	if (need_expand(content) == 0)
		return (content);
	res = new_expand_aux(content, res, flag, envp);
	free(content);
	return (res);
}

t_listp	*expansion(t_listp **token, char **envp)
{
	t_listp	*tmp;
	int		i;

	i = 0;
	if (!envp)
		return (NULL);
	tmp = *token;
	while (tmp)
	{
		i = 0;
		while (tmp->content2[i])
		{
			if (!(i > 0 && tmp->content2[i - 1] && \
				ft_strcmp(tmp->content2[i - 1], "<<") == 0))
				tmp->content2[i] = new_expand(tmp->content2[i], envp);
			i++;
		}
		tmp = tmp->next;
	}
	return (*token);
}
