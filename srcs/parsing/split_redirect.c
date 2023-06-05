/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:21:51 by ennollet          #+#    #+#             */
/*   Updated: 2023/05/26 18:41:38 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirection_end(char **split)
{
	int	i;

	i = ft_strslen(split) - 1;
	if (is_redirection(split[i][0]) == 1)
		return (printf("syntax error near unexpected token `%c'\n", \
		split[i][0]), 1);
	return (0);
}
