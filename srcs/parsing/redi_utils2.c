/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:30:54 by ennollet          #+#    #+#             */
/*   Updated: 2023/05/26 18:40:05 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_word2(char **str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (strcmp(str[i], " ") != 0)
			count++;
		i++;
	}
	return (count);
}

char	**realoc_split(char **s)
{
	int		i;
	int		j;
	char	**tab;

	if (!s)
		return (0);
	i = 0;
	j = 0;
	tab = (char **)malloc(sizeof(char *) * (count_word2(s) + 1));
	if (!tab)
		return (NULL);
	while (s[j])
	{
		if (strcmp(s[j], " ") != 0)
			tab[i++] = s[j];
		else
			free(s[j]);
		j++;
	}
	free(s);
	tab[i] = 0;
	return (tab);
}

int	is_redi(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	count_word3(char **s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] && s[i + 1] && is_redi(*s[i]) == 1 && s[i + 1] == s[i])
			i++;
		count++;
		i++;
	}
	return (count);
}

char	**realoc_split2(char **s)
{
	int		i;
	int		j;
	char	**tab;

	if (!s)
		return (0);
	i = 0;
	j = 0;
	tab = (char **)malloc(sizeof(char *) * (count_word3(s) + 1));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		if (s[i] && s[i + 1] && is_redi(*s[i]) == 1 && *s[i + 1] == *s[i])
		{
			tab[j++] = ft_strjoin(s[i], s[i + 1]);
			i++;
		}
		else
			tab[j++] = s[i];
		i++;
	}
	free(s);
	tab[j] = 0;
	return (tab);
}
