/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:31:17 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/21 11:56:12 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = '\0';
	if (s1)
		free(s1);
	return (res);
}

char	*get_key(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str && str[i] != '=')
		i++;
	if (str[i] != '=')
		return (NULL);
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i] != '=')
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

// char	**build_env(t_dict *dict)
// {
// 	int		size;
// 	char	**env;

// 	size = ft_dictsize(dict);
// 	env = (char **)malloc(sizeof(char *) * (size + 1));
// 	if (!env)
// 		return (NULL);
// 	size = 0;
// 	while (dict)
// 	{
// 		env[size] = ft_strjoin_char_env(dict->key, '=');
// 		env[size] = ft_strjoin_env(env[size], dict->content);
// 		size++;
// 		dict = dict->next;
// 	}
// 	env[size] = 0;
// 	return (env);
// }
