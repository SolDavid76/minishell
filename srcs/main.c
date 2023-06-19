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
		dup2(g_shell->savedin, 0);
		dup2(g_shell->savedout, 1);
	}
	else
	{
		g_shell = malloc(sizeof(t_shell));
		g_shell->pipeline = NULL;
		g_shell->envp = ft_envdup(envp);
		g_shell->savedin = dup(0);
		g_shell->savedout = dup(1);
		g_shell->here_docs = NULL;
		g_shell->cmds = NULL;
	}
	errno = 0;
}

void	ft_main_exit(int code)
{
	if (g_shell)
	{
		if (g_shell->pipeline)
		{
			free(g_shell->pipeline->pid);
			g_shell->pipeline = NULL;
		}
		dupnclose(g_shell->savedin, g_shell->savedout);
		here_doc_remove(g_shell->here_docs);
		ft_lst_free(g_shell->here_docs);
		free_tab_tab(g_shell->cmds);
		free_tab(g_shell->envp);
		free(g_shell);
	}
	exit(code);
}

//doit etre supprime a terme
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

void	minishell(void)
{
	t_listp	*lstp;
	char	*input;

	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	input = readline("minishell> ");
	lstp = parsing(input, g_shell->envp);
	free(input);
	if (!lstp)
		return ;
	g_shell->cmds = big_join(lstp);
	ft_lstclearp(lstp);
	ft_exec(g_shell->cmds, g_shell->envp);
	ft_shell_init(g_shell->envp);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	ft_shell_init(envp);
	g_shell->exit_value = 0;
	while (42)
		minishell();
}
