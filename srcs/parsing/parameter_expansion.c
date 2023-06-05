/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:41:31 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/01 11:36:59 by ennollet         ###   ########.fr       */
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
			if (flag != 1)
			{
				tmp = check_variable(content + i + 1, envp);
				res = ft_strjoin(res, tmp);
				i++;
				while (is_valid_variable(content[i]))
					i++;
			}
		}
		flag = new_expand_flag(flag, content[i]);
		if (content[i] && (content[i] != '$' || flag == 1))
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

t_list	*expansion(t_list **token, char **envp)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = *token;
	while (tmp)
	{
		i = 0;
		while (tmp->content2[i])
		{
			tmp->content2[i] = new_expand(tmp->content2[i], envp);
			i++;
		}
		tmp = tmp->next;
	}
	printf("after expansion\n");
	return (*token);
}
