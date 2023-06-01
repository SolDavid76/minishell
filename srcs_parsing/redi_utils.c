/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:20:01 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/01 14:11:45 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	count_word(char const *str, char *sep)
{
	int	i;
	int	count;
	int	flag;

	i = 0;
	count = 0;
	flag = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && is_sep(str[i], sep))
		{
			count++;
			i++;
		}
		if (str[i] != '\0')
			count++;
		while (str[i] != '\0' && (!(is_sep(str[i], sep)) || flag != 0))
		{
			flag = test_flag(flag, str[i]);
			i++;
		}
	}
	return (count);
}

static int	ft_word_len(char const *str, char *sep)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (is_sep(str[i], sep) == 1)
		return (1);
	while (str[i] && (!(is_sep(str[i], sep)) || flag != 0))
	{
		flag = test_flag(flag, str[i]);
		i++;
	}
	return (i);
}

static char	*ft_malloc_word(char const *str, char *sep)
{
	int		i;
	int		wl;
	char	*tab;

	i = 0;
	wl = ft_word_len(str, sep);
	tab = (char *)malloc(sizeof(char) * (wl + 1));
	if (!tab)
		return (NULL);
	while (i < wl)
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = 0;
	return (tab);
}

char	**split_redirect_aux(char **tab, char *sep, int flag, char *s)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		while (*s != '\0' && is_sep(*s, sep) && flag == 0)
		{
			tab[i++] = ft_malloc_word(s, sep);
			s++;
		}
		if (*s != '\0')
		{
			tab[i] = ft_malloc_word(s, sep);
			if (tab[i] == NULL)
				return (ft_free_all(tab, i - 1));
			i++;
		}
		while (*s != '\0' && ((!is_sep(*s, sep)) || flag != 0))
		{
			flag = test_flag(flag, *s);
			s++;
		}
	}
	tab[i] = 0;
	return (tab);
}

char	**split_redirect(char *s, char *sep)
{
	char	**tab;
	int		flag;

	if (!s)
		return (0);
	flag = 0;
	tab = (char **)malloc(sizeof(char *) * (count_word(s, sep) + 1));
	if (!tab)
		return (NULL);
	tab = split_redirect_aux(tab, sep, flag, s);
	return (tab);
}
