/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:22:46 by djanusz           #+#    #+#             */
/*   Updated: 2023/06/19 16:43:36 by ennollet         ###   ########.fr       */
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
	ft_redirection(cmd);
	if (!ft_strcmp(cmd[0], "echo"))
		echo(cmd + 1);
	if (!ft_strcmp(cmd[0], "cd"))
		cd(cmd[1], cmd);
	if (!ft_strcmp(cmd[0], "pwd"))
		pwd();
	if (!ft_strcmp(cmd[0], "export"))
		export(cmd[1], g_shell->dict);
	if (!ft_strcmp(cmd[0], "unset"))
		unset(cmd[1], g_shell->dict);
	if (!ft_strcmp(cmd[0], "env"))
		env(g_shell->envp);
	if (mod)
		ft_main_exit(g_shell->exit_value);
}

// void	echo(char **cmd)
// {
// 	int	option;
// 	int	i;

// 	option = !ft_strcmp(cmd[0], "-n");
// 	i = option;
// 	while (cmd[i])
// 	{
// 		write(1, cmd[i], ft_strlen(cmd[i]));
// 		if (cmd[i + 1])
// 			write(1, " ", 1);
// 		i++;
// 	}
// 	if (!option)
// 		write(1, "\n", 1);
// }

// void	pwd(char **cmd)
// {
// 	int		size;
// 	char	*buf;

// 	if (cmd[1] != NULL)
// 	{
// 		write(2, "pwd: too many arguments\n", 24);
// 		return ;
// 	}
// 	size = 1;
// 	buf = NULL;
// 	while (!buf)
// 		buf = getcwd(buf, size++);
// 	write(1, buf, ft_strlen(buf));
// 	write(1, "\n", 1);
// }

// void	unset(t_shell *shell, char *key)
// {
// 	t_dict	*tmp;

// 	tmp = ft_dict_find(shell->env, key);
// 	if (tmp && tmp == shell->env)
// 		shell->env = shell->env->next;
// 	ft_dict_del(tmp);
// }

// void	env(t_shell *shell)
// {
// 	t_dict	*tmp;

// 	tmp = shell->env;
// 	while (tmp)
// 	{
// 		write(1, tmp->key, ft_strlen(tmp->key));
// 		write(1, "=", 1);
// 		write(1, tmp->content, ft_strlen(tmp->content));
// 		write(1, "\n", 1);
// 		tmp = tmp->next;
// 	}
// }
