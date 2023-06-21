/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:53:55 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/21 17:57:50 by ennollet         ###   ########.fr       */
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
	t_dict	*tmp;
	int		flag;

	tmp = dict;
	key = get_key(str);
	content = get_content(str);
	flag = 0;
	while (tmp && flag == 0)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->content);
			free(key);
			tmp->content = content;
			flag = 1;
		}
		tmp = tmp->next;
	}
	if (flag == 0)
		dict = add_dict(dict, key, content);
	free_tab(g_shell->envp);
	return (dict);
}

void	export_aux2(char *str, int i, t_dict *dict)
{
	if (str[i])
	{
		g_shell->dict = export_aux(str, dict);
		g_shell->envp = build_env(g_shell->dict);
	}
}

void	export(char **cmd, t_dict *dict, int i)
{
	if (!cmd[0])
	{
		export_without_arg(dict);
		return ;
	}
	while (*cmd)
	{
		i = 0;
		if (cmd[i][0] >= '0' && cmd[i][0] <= '9')
		{
			g_shell->exit_value = 1;
			printf("export: `%s': not a valid identifier\n", *cmd);
		}
		while ((*cmd)[i] && (*cmd)[i] != '=')
		{
			if (!(is_valid_variable((*cmd)[i++])))
			{
				g_shell->exit_value = 2;
				printf("export: `%s': not a valid identifier\n", *cmd);
			}
		}
		export_aux2(*cmd, i, dict);
		cmd++;
	}
}
