/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:01:43 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/01 14:11:38 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*free_split(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

void	ft_lstclearp(t_listp	*lst)
{
	t_listp	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->content);
		// free_split(lst->content2);
		free(lst);
		lst = tmp;
	}
}

void	print_list(t_listp **lst)
{
	t_listp	*tmp;
	int		i;

	tmp = *lst;
	i = 0;
	while (tmp)
	{
		printf("char  %d * : %s \n", i, tmp->content);
		tmp = tmp->next;
		i++;
	}
	printf("\n");
}

void	print_command(t_listp **lst)
{
	t_listp	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = *lst;
	while (tmp)
	{
		i = 0;
		while (tmp->content2[i])
		{
			printf("char %d %d ** : %s\n", j, i, tmp->content2[i]);
			i++;
		}
		j++;
		tmp = tmp->next;
	}
	printf("\n");
}
