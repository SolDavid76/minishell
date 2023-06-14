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

void	ft_shell_init(char **envp)
{
	if (g_shell)
	{
		g_shell->cmds = free_tab_tab(g_shell->cmds);
		here_doc_remove(g_shell->here_docs);
		g_shell->here_docs = ft_lst_free(g_shell->here_docs);
	}
	else
	{
		g_shell = malloc(sizeof(t_shell));
		g_shell->envp = ft_envdup(envp);
		g_shell->here_docs = NULL;
		g_shell->cmds = NULL;
	}
	errno = 0;
}

void	ft_main_exit(int code)
{
	if (g_shell)
	{
		here_doc_remove(g_shell->here_docs);
		ft_lst_free(g_shell->here_docs);
		free_tab_tab(g_shell->cmds);
		free_tab(g_shell->envp);
		free(g_shell);
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
		lst = lst->next;
		i++;
	}
	res[i] = 0;
	return (res);
}

int	main(int ac, char **av, char **envp)
{
	t_listp	*lstp;
	char	*input;

	(void)ac;
	(void)av;
	ft_shell_init(envp);
	g_shell->exit_value = 0;
	while (42)
	{
		fprintf(stderr, "$? = %d\n", g_shell->exit_value); //debug
		input = readline("un joli prompt > ");
		lstp = parsing(input, g_shell->envp);
		free(input);
		if (!lstp)
			continue ;
		g_shell->cmds = big_join(lstp);
		ft_lstclearp(lstp);
		ft_exec(g_shell->cmds, g_shell->envp);
		ft_shell_init(envp);
	}
}
