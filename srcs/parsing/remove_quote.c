/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:57:31 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/01 11:37:24 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_strlen(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (!str)
// 		return (0);
// 	while (str[i])
// 		i++;
// 	return (i);
// }

int	find_end(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*remove_quote_aux(char *tmp)
{
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	while (tmp[i])
	{
		if (tmp[i] == '"' && find_end(tmp + i, tmp[i]) == 1)
		{
			while (tmp[++i] && tmp[i] != '"')
				res = ft_strjoin_char(res, tmp[i]);
			i++;
		}
		else if (tmp[i] == '\'' && find_end(tmp + i, tmp[i]) == 1)
		{
			while (tmp[++i] && tmp[i] != '\'')
				res = ft_strjoin_char(res, tmp[i]);
			i++;
		}
		else
			res = ft_strjoin_char(res, tmp[i++]);
	}
	free(tmp);
	return (res);
}

t_listp	*remove_quote(t_listp **token)
{
	t_listp	*tmp;
	int		i;

	i = 0;
	tmp = *token;
	while (tmp)
	{
		i = 0;
		while (tmp->content2[i])
		{
			tmp->content2[i] = remove_quote_aux(tmp->content2[i]);
			i++;
		}
		tmp = tmp->next;
	}
	printf("after remove quote\n");
	return (*token);
}
