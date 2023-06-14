/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:04:48 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/13 16:37:59 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dict	*suppr(t_dict *dict, t_dict *next)
{
	if (dict != NULL)
	{
		free(next->key);
		free(next->content);
		dict->next = dict->next->next;
		free(next);
		return (dict);
	}
	else
	{
		free(next->key);
		free(next->content);
		next = next->next;
	}
	return (next);
}

t_dict	*ft_unset(char *var, t_dict *dict)
{
	t_dict *tmp;
	
	tmp = dict;
	if (strcmp(var, tmp->key) == 0)
	{
		tmp = suppr(NULL, tmp);
		return (tmp);
	}
	while (tmp->next != NULL)
	{
		if (strcmp(var, tmp->next->key) == 0)
			suppr(tmp, tmp->next);
		tmp = tmp->next;
	}
	return (dict);
}


void	export_without_arg(t_dict *dict)
{
	t_dict	*tmp;

	tmp = dict;
	while (tmp->next != NULL)
	{
		printf("export %s=\"%s\"\n", tmp->key, tmp->content);
		tmp = tmp->next;
	}
}

t_dict	*ft_export(t_dict *dict, char *key, char *content)
{
	t_dict	*tmp;

	tmp = dict;
	while (tmp->next != NULL)
	{
		if (strcmp(key, tmp->key) == 0)
		{
			free(tmp->content);
			tmp->content = ft_strdup(content);
			return (dict);
		}
		tmp = tmp->next;
	}
	ft_dictadd_back(&dict, ft_dictnew(ft_strdup(content), ft_strdup(key)));
	return (dict);
}

