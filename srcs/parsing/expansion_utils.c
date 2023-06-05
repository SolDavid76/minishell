/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 09:56:15 by ennollet          #+#    #+#             */
/*   Updated: 2023/05/31 10:09:20 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
	{
		i++;
	}
	if (n > 0)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

char	*ft_strjoin_char(char *str, char c)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!res)
		return (free(str), NULL);
	i = 0;
	while (str && str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i++] = c;
	res[i] = '\0';
	return (free(str), res);
}

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	int		i;
// 	int		j;
// 	char	*tab;

// 	i = 0;
// 	j = 0;
// 	tab = (char *)malloc(sizeof(*s1) * ft_strlen(s1) + ft_strlen(s2) + 1);
// 	if (!tab)
// 		return (NULL);
// 	while (s1 && s1[i] != '\0')
// 	{
// 		tab[i] = s1[i];
// 		i++;
// 	}
// 	while (s2 && s2[j] != '\0')
// 	{
// 		tab[i + j] = s2 [j];
// 		j++;
// 	}
// 	tab[i + j] = '\0';
// 	if (s2)
// 		free(s2);
// 	if (s1)
// 		free(s1);
// 	return (tab);
// }

int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z' ) || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	is_valid_variable(char c)
{
	if (is_alpha(c) || (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}
