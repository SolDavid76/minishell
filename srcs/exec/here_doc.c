/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:23:41 by djanusz           #+#    #+#             */
/*   Updated: 2023/06/27 17:18:46 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

void	*here_doc_remove(t_list *docs)
{
	while (docs && docs->content)
	{
		unlink(docs->content);
		docs = docs->next;
	}
	return (NULL);
}

t_list	*here_doc_write(t_list *docs, t_list *input, char *eof, int fd)
{
	char	*str;
	int		i;

	while (input && ft_strcmp(input->content, eof))
	{
		i = 0;
		str = input->content;
		while (str && str[i])
		{
			if (str[i] == '$')
			{
				ft_print_var(g_shell->envp, str + 1 + i++, fd);
				i += (str[i] == '?');
				while (is_in_variable(str[i]) && str[i - 1] != '?')
					i++;
			}
			else
				write(fd, str + i++, 1);
		}
		if (str)
			write(fd, "\n", 1);
		input = input->next;
	}
	return (close(fd), docs);
}

t_list	*here_doc_open(t_list *docs, t_list *input, char *eof)
{
	char	*str;
	int		fd;
	int		i;

	i = 0;
	fd = -1;
	str = NULL;
	while (fd == -1 && g_shell->exit_value == 0)
	{
		if (str)
			free(str);
		str = ft_strjoin(ft_strdup(".here_doc"), ft_itoa(i++));
		fd = open(str, O_CREAT + O_EXCL + O_RDWR, 0666);
		if (fd != -1)
			ft_lstadd_back(&docs, ft_lstnew(str));
	}
	if (g_shell->exit_value == 0)
		return (here_doc_write(docs, input, eof, fd));
	return (docs);
}

t_list	*here_doc_aux(t_list *docs, char **cmd, int x)
{
	t_list	*input;
	int		i;

	i = -1;
	input = ft_lstnew(NULL);
	while (g_shell->exit_value == 0 && (i == -1 || (ft_lstlast(input)->content
				&& ft_strcmp(ft_lstlast(input)->content, cmd[x + 1]))))
	{
		ft_lstadd_back(&input, ft_lstnew(readline("heredoc> ")));
		i++;
	}
	if (!ft_lstlast(input)->content && g_shell->exit_value == 0)
		here_doc_error(cmd[x + 1], i);
	docs = here_doc_open(docs, input, cmd[x + 1]);
	ft_lst_free(input);
	if (docs && docs->content)
	{
		free(cmd[x + 1]);
		cmd[x + 1] = ft_strdup(ft_lstlast(docs)->content);
	}
	return (docs);
}

t_list	*here_doc(char ***cmds)
{
	t_list	*docs;
	int		i;
	int		j;

	i = 0;
	docs = NULL;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i][j])
		{
			if (!ft_strcmp(cmds[i][j], "<<"))
				docs = here_doc_aux(docs, cmds[i], j);
			j++;
		}
		i++;
	}
	return (docs);
}
