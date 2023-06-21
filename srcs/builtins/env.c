/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:57:05 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/21 15:20:21 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

void	env(char **envp, char **cmd)
{
	int	i;

	i = 0;
	if (cmd[0] && cmd[1])
	{
		write(2, "env: too many arguments\n", 24);
		g_shell->exit_value = 127;
		return ;
	}
	while (envp[i])
		printf("%s\n", envp[i++]);
}

char	**build_env(t_dict *dict)
{
	int		size;
	char	**env;

	size = ft_dictsize(dict);
	env = (char **)malloc(sizeof(char *) * (size + 1));
	if (!env)
		return (NULL);
	size = 0;
	while (dict)
	{
		env[size] = ft_strjoin_char_env(dict->key, '=');
		env[size] = ft_strjoin_env(env[size], dict->content);
		size++;
		dict = dict->next;
	}
	env[size] = 0;
	return (env);
}
