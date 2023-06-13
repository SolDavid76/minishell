/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 09:59:57 by djanusz           #+#    #+#             */
/*   Updated: 2023/06/13 09:59:57 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*g_shell = NULL;

//ne pas reset g_shell->exit_value car 
//si on en a besoin dans la commande l'info est detruite
void	ft_shell_init(char **envp)
{
	if (g_shell)
	{
		g_shell->cmds = free_tab_tab(g_shell->cmds);
	}
	else
	{
		g_shell = malloc(sizeof(t_shell));
		g_shell->dict = NULL;
		g_shell->envp = ft_envdup(envp);
		g_shell->cmds = NULL;
	}
}

void	ft_main_exit(int code)
{
	t_shell	*shell;

	shell = g_shell;
	if (shell)
	{
		free_tab(shell->envp);
		free(shell);
	}
	exit(code);
}

char	**ft_envdup(char **envp)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (ft_tablen(envp) + 1));
	if (!res)
		exit(1);
	i = -1;
	while (envp[++i])
		res[i] = ft_strdup(envp[i]);
	res[i] = NULL;
	return (res);
}

char	***big_join(t_listp *lst)
{
	char	***res;
	int		size;
	int		i;

	size = ft_lstsizep(lst);
	res = (char ***)malloc(sizeof(char **) * (size + 1));
	i = 0;
	if (!res)
		return (NULL);
	while (i < size)
	{
		res[i] = lst->content2;
		lst = lst->next ;
		i++;
	}
	res[i] = 0;
	return (res);
}

int	main(int ac, char **av, char **envp)
{
	t_listp	*bob;
	char	*input;

	while (42)
	{
		ft_shell_init(envp);
		input = readline("un joli prompt > ");
		bob = parsing(input, g_shell->envp);
		free(input);
		if (!bob)
			continue ;
		g_shell->cmds = big_join(bob);
		ft_exec(g_shell->cmds, g_shell->envp);
		ft_lstclearp(bob);
	}
	(void)ac;
	(void)av;
	ft_main_exit(0);
}
// fprintf(stderr, "$? = %d\n", g_shell->exit_value);
