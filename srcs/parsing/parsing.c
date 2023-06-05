/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:01:50 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/02 10:25:59 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*parsing_aux(t_list *bob, char *tmp, char **envp)
{
	add_history(tmp);
	printf("readline : %s\n", tmp);
	bob = lexer2(tmp, bob);
	if (bob != NULL)
	{
		bob = expansion(&bob, envp);
		print_command(&bob);
	}
	if (bob != NULL)
	{
		bob = remove_quote(&bob);
		print_command(&bob);
	}
	if (bob != NULL)
	{
		bob = substitution(&bob, envp);
		print_command(&bob);
		printf("list size %d\n", ft_lstsize(bob));
	}
	return (bob);
}

t_list	*parsing(char **envp)
{
	t_list	*bob;
	char	*tmp;

	while (1)
	{
		tmp = readline("Enter text: ");
		if (tmp)
			return (parsing_aux(bob, tmp, envp));
		else
			return (0);
	}
	return (0);
}
