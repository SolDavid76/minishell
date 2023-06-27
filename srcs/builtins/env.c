/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:57:05 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/23 19:36:00 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

void	env(char **envp, char **cmd)
{
	t_dict	*tmp;

	tmp = g_shell->dict;
	if (cmd[0] && cmd[1])
	{
		write(2, "env: too many arguments\n", 24);
		g_shell->exit_value = 127;
		return ;
	}
	while (tmp)
	{
		if (tmp->key && tmp->content)
			printf("%s=%s\n", tmp->key, tmp->content);
		tmp = tmp->next;
	}
	(void)envp;
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

char	*ft_strjoin_char_env(char *str, char c)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (str && str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i++] = c;
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin_env(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!res)
		exit(1);
	i = 0;
	j = 0;
	if (s1)
		while (s1[i])
			res[j++] = s1[i++];
	i = 0;
	if (s2)
		while (s2[i])
			res[j++] = s2[i++];
	res[j] = '\0';
	if (s1)
		free(s1);
	return (res);
}
