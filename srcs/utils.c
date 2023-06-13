/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:22:23 by djanusz           #+#    #+#             */
/*   Updated: 2023/06/13 10:22:23 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != 0 && s2[i] != 0 && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strdup(char *str)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		exit(1);
	i = -1;
	while (str[++i])
		res[i] = str[i];
	res[i] = '\0';
	return (res);
}


char	*ft_strjoin(char *s1, char *s2)
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
	if (s2)
		free(s2);
	return (res);
}
