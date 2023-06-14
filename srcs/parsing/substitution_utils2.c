/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:50:09 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/14 15:00:26 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_buildinp(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

char	*check_path(char **path_split, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!path_split)
		return (NULL);
	if (is_buildinp(str) != 1)
	{
		while (path_split[i])
		{
			tmp = ft_strjoin_char(path_split[i], '/');
			tmp = ft_strjoin2(tmp, str);
			if (access(tmp, F_OK) != -1)
			{
				free_split_s(path_split, i + 1);
				return (tmp);
			}
			free(tmp);
			i++;
		}
	}
	free_split_s(path_split, i);
	return (str);
}

char	*check_file_exist(char *command)
{
	if (access(command, F_OK) != -1)
	{
		if (access(command, X_OK) != -1)
			return (command);
	}
	return (NULL);
}

char	*command_sub(char *str, char **envp)
{
	char	**split;
	char	*tmp;
	char	*res;

	split = get_path_line(envp);
	if (split == NULL)
		return (str);
	tmp = str;
	res = check_path(split, tmp);
	if (str != res)
		free(str);
	return (res);
}
