/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acces.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:27:19 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/01 11:34:56 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirection(char *str)
{
	if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0 || \
	ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0)
		return (1);
	return (0);
}

int	ft_strslen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

t_listp	*substitution(t_listp **token, char **envp)
{
	t_listp	*tmp;
	int		i;
	int		flag;

	tmp = *token;
	while (tmp)
	{
		i = 0;
		flag = 0;
		while (ft_strslen(tmp->content2) > i && tmp->content2[i] && flag == 0)
		{
			if (tmp->content2 && check_redirection(tmp->content2[i]) == 0)
			{
				tmp->content2[i] = command_sub(tmp->content2[i], envp);
				flag = 1;
				i++;
			}
			else
				i += 2;
		}
		tmp = tmp->next;
	}
	printf("after substitution\n");
	return (*token);
}
