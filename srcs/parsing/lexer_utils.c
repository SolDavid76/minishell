/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:43:43 by ennollet          #+#    #+#             */
/*   Updated: 2023/05/31 15:30:09 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;
	size_t	x;

	x = nmemb * size;
	if (x != 0 && x / nmemb != size)
		return (NULL);
	tab = (void *)malloc(x);
	if (!tab)
		return (NULL);
	ft_bzero(tab, x);
	return (tab);
}

char	*ft_strndup(char *s, size_t size)
{
	char		*tab;
	size_t		i;

	i = 0;
	tab = (char *)malloc(sizeof(char) * size + 1);
	if (!tab)
		return (NULL);
	while (s[i] && i < size)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

int	is_token(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

int	is_redirection(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}
