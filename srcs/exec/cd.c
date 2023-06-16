/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:27:23 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/16 12:22:50 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#include <linux/limits.h>

extern t_shell	*g_shell;


void printf_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if(ft_strncmp(envp[i], "PWD", 3) == 0 || (ft_strncmp(envp[i], "OLDPWD", 6) == 0))
			printf("%s\n", envp[i]);
		i++;
	}
}

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


void	cd(char	*path)
{
	char	tmp[PATH_MAX];
	char	tmp2[PATH_MAX];
	t_dict	*test;
	
	test = g_shell->dict;
	getcwd(tmp2, sizeof(tmp));
	if (chdir(path) == 0)
	{
		if (check_dict("OLDPWD") == 1)
		{
			// getcwd(tmp, sizeof(tmp));
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
			// chdir(path);
			getcwd(tmp, sizeof(tmp));
			free(test->content);
			test->content = ft_strdup(tmp);
		}
	}
}

int main(int ac, char **av, char **envp)
{
	ft_shell_init(envp);
	free_tab(g_shell->envp);

	g_shell->dict = get_dict(envp);
	g_shell->envp = build_env(g_shell->dict);
	printf_env(g_shell->envp);
	cd("../");
	free_tab(g_shell->envp);
	g_shell->envp = build_env(g_shell->dict);
	printf_env(g_shell->envp);
	free_tab(g_shell->envp);
	ft_dictclear(g_shell->dict);
	free(g_shell);

	(void)ac;
	(void)av;
}