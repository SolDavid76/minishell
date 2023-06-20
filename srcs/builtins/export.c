/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:53:55 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/19 15:50:51 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

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
	ft_dictadd_back(&dict, ft_dictnew(content, key));
	return (dict);
}

void	*export_aux(char *str, t_dict *dict)
{
	char	*key;
	char	*content;

	key = get_key(str);
	content = get_content(str);
	dict = add_dict(dict, key, content);
	free_tab(g_shell->envp);
	return (dict);
}

void	export(char *str, t_dict *dict)
{
	int		i;

	i = 0;
	if (!str)
	{
		export_without_arg(dict);
		return ;		
	}
	if (str[i] >= '0' && str[i] <= '9')
	{
		g_shell->exit_value = 1;
		printf("export: `%s': not a valid identifier\n", str);
	}
	while (str[i] && str[i] != '=')
	{
		if (!(is_valid_variable(str[i++])))
		{
			g_shell->exit_value = 2;
			printf("export: `%s': not a valid identifier\n", str);
		}
	}
	if (str[i])
	{
		g_shell->dict = export_aux(str, dict);
		g_shell->envp = build_env(g_shell->dict);
	}
}