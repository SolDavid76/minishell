/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:15:34 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/21 14:49:50 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#include <linux/limits.h>

extern t_shell	*g_shell;

int	check_dict(char *key)
{
	t_dict	*tmp;

	tmp = g_shell->dict;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	cd_aux(t_dict *test, char tmp2[PATH_MAX])
{
	char	tmp[PATH_MAX];

	getcwd(tmp2, sizeof(tmp));
	if (check_dict("OLDPWD") == 1)
	{
		while (strcmp(test->key, "OLDPWD") != 0)
			test = test->next;
		free(test->content);
		test->content = ft_strdup(tmp2);
	}
	if (check_dict("PWD") == 1)
	{
		test = g_shell->dict;
		while (strcmp(test->key, "PWD") != 0)
			test = test->next;
		getcwd(tmp, sizeof(tmp));
		free(test->content);
		test->content = ft_strdup(tmp);
	}
	free_tab(g_shell->envp);
	g_shell->envp = build_env(g_shell->dict);
}

int	cd_aux2(char **cmd, char **path)
{
	if (ft_strslen(cmd) > 2)
	{
		write(2, "cd: too many arguments\n", 24);
		g_shell->exit_value = 1;
		return (1);
	}
	else if (!(*path) && check_dict("HOME") == 1)
	{
		*path = check_variable("HOME", g_shell->envp);
		return (0);
	}
	else if (!(*path))
	{
		write (2, "bash: cd: HOME not set\n", 24);
		g_shell->exit_value = 1;
		return (1);
	}
	return (1);
}

void	cd(char *path, char **cmd)
{
	char	tmp2[PATH_MAX];
	t_dict	*test;
	int		flag;

	test = g_shell->dict;
	getcwd(tmp2, sizeof(tmp2));
	flag = cd_aux2(cmd, &path);
	if (chdir(path) == 0)
		cd_aux(test, tmp2);
	else
	{	
		perror("cd: ");
		g_shell->exit_value = 1;
	}
	if (!flag)
		free(path);
}
