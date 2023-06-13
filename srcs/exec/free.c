/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:23:31 by djanusz           #+#    #+#             */
/*   Updated: 2023/06/13 10:23:32 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

void	free_tab_tab(char ***ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
		free_tab(ptr[i++]);
	free(ptr);
}
