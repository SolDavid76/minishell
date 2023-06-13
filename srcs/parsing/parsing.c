/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:01:50 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/13 17:18:31 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_listp	*parsing_aux(t_listp *bob, char *tmp, char **envp)
{
	add_history(tmp);
	// printf("readline : %s\n", tmp);
	bob = lexer2(tmp, bob);
	if (bob != NULL)
	{
		bob = expansion(&bob, envp);
		// print_command(&bob);
	}
	if (bob != NULL)
	{
		bob = remove_quote(&bob);
		// print_command(&bob);
	}
	if (bob != NULL)
	{
		bob = substitution(&bob, envp);
		// print_command(&bob);
		// printf("list size %d\n", ft_lstsizep(bob));
	}
	return (bob);
}

t_listp	*parsing(char *tmp, char **envp)
{
	t_listp	*bob;

	bob = NULL;
	while (1)
	{
		if (tmp)
			return (parsing_aux(bob, tmp, envp));
		else
			return (0);
	}
	return (0);
}
