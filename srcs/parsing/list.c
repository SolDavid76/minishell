/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:44:53 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/02 10:03:46 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_listp	*ft_lstnewp(char *content, int len)
{
	t_listp	*new;
	char	*dup;

	new = malloc(sizeof(t_listp));
	if (!new)
		return (NULL);
	dup = ft_strndup(content, len);
	if (!dup)
		return (NULL);
	new->content = dup;
	new->next = NULL;
	return (new);
}

t_listp	*ft_lstlastp(t_listp *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_backp(t_listp **lst, t_listp *new)
{
	t_listp	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlastp(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

int	ft_lstsizep(t_listp *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
