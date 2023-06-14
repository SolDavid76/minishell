/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:46:25 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/14 15:47:02 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

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
	t_dict	*tmp;

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

t_dict	*add_dict(t_dict *dict, char *key, char *content)
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

void	*export_aux(char *str, t_dict *dict)
{
	char	*key;
	char	*content;

	key = get_key(str);
	content = get_content(str);
	dict = add_dict(dict, key, content);
	return (dict);
}

t_dict	*export(char *str, t_dict *dict)
{
	int		i;

	i = 0;
	if (!str)
	{
		export_without_arg(dict);
		return (dict);
	}
	if (str[i] >= '0' && str[i] <= '9')
	{
		g_shell->exit_value = 1;
		return (printf("export: `%s': not a valid identifier", str), dict);
	}
	while (str[i])
	{
		if (!(is_valid_variable(str[i++])))
		{
			g_shell->exit_value = 2;
			return (printf("export: `%s': not a valid identifier", str), dict);
		}
	}
	dict = export_aux(str, dict);
	return (dict);
}