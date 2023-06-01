/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:01:50 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/01 16:18:51 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*parsing(t_list *bob, char *tmp, char **envp)
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
	}
	return (bob);
}

int	main(int ac, char **av, char **envp)
{
	t_list	*bob;
	char	*tmp;

	while (1)
	{
		tmp = readline("Enter text: ");
		if (tmp)
		{
			bob = parsing(bob, tmp, envp);
			free(tmp);
			ft_lstclear(bob);
		}
		else
			return (0);
		(void)ac;
		(void)av;
	}	
	return (0);
}
