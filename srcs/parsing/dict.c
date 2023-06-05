/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:31:17 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/02 16:42:15 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*get_key(char *str)
// {
// 	int		i;
// 	char	*res;

// 	i = 0;
// 	while (str && str[i] != '=')
// 		i++;
// 	if (str[i] != '=')
// 		return (NULL);
// 	res = (char *)malloc(sizeof(char) * (i + 1));
// 	if (!res)
// 		return (NULL);
// 	i = 0;
// 	while (str[i] != '=')
// 	{
// 		res[i] = str[i];
// 		i++;
// 	}
// 	res[i] = 0;
// 	return (res);
// }

// char	*get_content(char *str)
// {
// 	int		i;
// 	char	*res;
// 	int		j;

// 	i = 0;
// 	while (str[i] && str[i] != '=')
// 		i++;
// 	j = 0;
// 	if (str[i] != '=')
// 		return (NULL);
// 	i++;
// 	while (str[j])
// 		j++;
// 	res = (char *)malloc(sizeof(char) * (j - i + 1));
// 	if (!res)
// 		return (NULL);
// 	j = 0;
// 	while (str[i])
// 		res[j++] = str[i++];
// 	res[j] = 0;
// 	return (res);
// }

// t_dict	*get_dict(char **envp)
// {
// 	int		i;
// 	t_dict	*dict;

// 	i = 0;
// 	dict = NULL;
// 	while (envp[i])
// 	{
// 		ft_dictadd_back(&dict, ft_dictnew(get_content(envp[i]), \
// 		get_key(envp[i]), 1));
// 		i++;
// 	}
// 	print_dict(&dict);
// 	return (dict);
// }

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
// 		env[size] = ft_strjoin_char(dict->key, '=');
// 		env[size] = ft_strjoin(env[size], dict->content);
// 		size++;
// 	}
// 	env[size] = 0;
// 	return (env);
// }

// int	main(int ac, char **av, char **envp)
// {
// 	t_dict	*dict;

// 	dict = get_dict(envp);
// }
