/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:01:50 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/21 12:10:44 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

t_listp	*parsing_aux(t_listp *bob, char *tmp, char **envp)
{
	add_history(tmp);
	bob = lexer2(tmp, bob);
	if (bob != NULL)
	{
		bob = expansion(&bob, envp);
	}
	if (bob != NULL)
	{
		bob = remove_quote(&bob);
	}
	if (bob != NULL)
	{
		bob = substitution(&bob, envp);
	}
	return (bob);
}

t_listp	*parsing(char *tmp, char **envp)
{
	t_listp	*bob;

	bob = NULL;
	if (tmp == NULL)
		ft_main_exit(g_shell->exit_value);
	while (1)
	{
		if (tmp)
			return (parsing_aux(bob, tmp, envp));
		else
			return (0);
	}
	return (0);
}
