/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:46:25 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/23 19:29:22 by ennollet         ###   ########.fr       */
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
		next->content = NULL;
		next->key = NULL;
		dict->next = dict->next->next;
		free(next);
		return (dict);
	}
	else
	{
		free(next->key);
		free(next->content);
		next->content = NULL;
		next->key = NULL;
		next = next->next;
	}
	return (next);
}

void	unset(char **cmd, t_dict *dict)
{
	t_dict	*tmp;
	int		i;

	if (!dict)
		return ;
	i = 0;
	while (cmd[i])
	{
		tmp = dict;
		if (ft_strcmp(cmd[i], tmp->key) == 0)
			tmp = suppr(NULL, tmp);
		while (tmp != NULL && tmp->next != NULL)
		{
			if (ft_strcmp(cmd[i], tmp->next->key) == 0)
				suppr(tmp, tmp->next);
			tmp = tmp->next;
		}
		free_tab(g_shell->envp);
		g_shell->envp = build_env(g_shell->dict);
		i++;
	}
}
