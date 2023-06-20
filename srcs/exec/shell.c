/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:23:49 by djanusz           #+#    #+#             */
/*   Updated: 2023/06/20 18:29:01 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

int	is_in_variable(char c)
{
	if ((('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')
			|| ('0' <= c && c <= '9') || c == '_'))
		return (1);
	return (0);
}

void	ft_print_var(char **envp, char *key, int fd)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	res = NULL;
	if (key[0] == '?')
		res = ft_itoa(g_shell->exit_value);
	while (envp[i] && !res)
	{
		j = 0;
		while (key[j] == envp[i][j] && is_valid_variable(key[j]))
			j++;
		if (!is_valid_variable(key[j]) && envp[i][j] == '=')
			res = ft_strdup(envp[i] + j + 1);
		i++;
	}
	write(fd, res, ft_strlen(res));
	free(res);
}
