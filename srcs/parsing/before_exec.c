/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:04:20 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/02 10:26:40 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

char	***big_join(t_list *lst)
{
	char	***res;
	int		size;
	int		i;

	size = ft_lstsize(lst);
	res = (char ***)malloc(sizeof(char **) * (size + 1));
	i = 0;
	if (!res)
		return (NULL);
	while (i < size)
	{
		res[i] = lst->content2;
		lst = lst->next ;
		i++;
	}
	res[i] = 0;
	return (res);
}

void	print_big(char ***big)
{
	int	i;
	int	j;

	i = 0;
	while (big[i])
	{
		j = 0;
		while (big[i][j])
		{
			printf("char %d %d *** : %s\n", i, j, big[i][j]);
			j++;
		}
		i++;
	}
}
