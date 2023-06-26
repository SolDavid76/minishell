/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:31:17 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/26 12:58:06 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dict	*add_dict(t_dict *dict, char *key, char *content)
{
	t_dict	*tmp;

	tmp = dict;
	while (tmp->next != NULL)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			free(tmp->content);
			tmp->content = ft_strdup(content);
			return (dict);
		}
		tmp = tmp->next;
	}
	ft_dictadd_back(&dict, ft_dictnew(content, key));
	return (dict);
}

char	*get_key(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char	*get_content(char *str)
{
	int		i;
	char	*res;
	int		j;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	j = 0;
	if (str[i] != '=')
		return (NULL);
	i++;
	while (str[j])
		j++;
	res = (char *)malloc(sizeof(char) * (j - i + 1));
	if (!res)
		return (NULL);
	j = 0;
	while (str[i])
		res[j++] = str[i++];
	res[j] = 0;
	return (res);
}

t_dict	*get_dict(char **envp)
{
	int		i;
	t_dict	*dict;

	i = 0;
	dict = NULL;
	while (envp[i])
	{
		ft_dictadd_back(&dict, ft_dictnew(get_content(envp[i]), \
		get_key(envp[i])));
		i++;
	}
	return (dict);
}
