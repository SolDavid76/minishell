/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substiution_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:58:29 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/14 14:49:13 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	while (s1[i] != 0 && s2[i] != 0 && s1[i] == s2[i])
// 		i++;
// 	return (s1[i] - s2[i]);
// }

char	**get_path_line(char **env)
{
	char	**path_split;
	int		i;

	i = 0;
	path_split = NULL;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			path_split = ft_split(env[i] + 5, ':');

		i++;	
	}
	return (path_split);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*tab;

	i = 0;
	j = 0;
	tab = (char *)malloc(sizeof(*s1) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!tab)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		tab[i] = s1[i];
		i++;
	}
	while (s2 && s2[j] != '\0')
	{
		tab[i + j] = s2 [j];
		j++;
	}
	tab[i + j] = '\0';
	if (s1)
		free(s1);
	return (tab);
}

void	*free_split_s(char **split, int i)
{
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}
