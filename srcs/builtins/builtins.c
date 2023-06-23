/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:22:46 by djanusz           #+#    #+#             */
/*   Updated: 2023/06/23 18:55:35 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

int	is_buildin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void	exec_buildin(char **cmd, int mod)
{
	if (!ft_strcmp(cmd[0], "echo"))
		echo(cmd + 1);
	if (!ft_strcmp(cmd[0], "cd"))
		cd(cmd[1], cmd);
	if (!ft_strcmp(cmd[0], "pwd"))
		pwd();
	if (!ft_strcmp(cmd[0], "export"))
		export(cmd + 1, g_shell->dict, 0);
	if (!ft_strcmp(cmd[0], "unset"))
		unset(cmd + 1, g_shell->dict);
	if (!ft_strcmp(cmd[0], "env"))
		env(g_shell->envp, cmd);
	if (!ft_strcmp(cmd[0], "exit"))
		exec_exit(cmd + 1);
	if (mod)
		ft_main_exit(g_shell->exit_value);
}
