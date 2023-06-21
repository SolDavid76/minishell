/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:40:14 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/21 14:51:12 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dict	*ft_dictnew(char *content, char *key)
{
	t_dict	*new;

	new = malloc(sizeof(t_listp));
	if (!new)
		return (NULL);
	new->content = content;
	new->key = key;
	new->next = NULL;
	return (new);
}

t_dict	*ft_dictlast(t_dict *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_dictadd_back(t_dict **lst, t_dict *new)
{
	t_dict	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_dictlast(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

int	ft_dictsize(t_dict *lst)
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

void	ft_dictclear(t_dict	*lst)
{
	t_dict	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst->key);
		free(lst);
		lst = tmp;
	}
}
