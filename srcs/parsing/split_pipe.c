/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 07:21:09 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/01 14:12:03 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *str)
{
	printf("syntax error near unexpected token `%s'\n", str);
	return (0);
}

t_listp	*split_pipe(char	*str)
{
	char	**split;
	int		i;
	t_listp	*lst;

	if (end_pipe(str) == 1 || start_pipe(str) == 1 || \
	test_multi(str) == 1 || check_triple(str) == 1)
		return (print_error("|"), NULL);
	split = ft_split_quote(str, "|");
	i = 0;
	lst = NULL;
	while (split[i])
	{
		ft_lstadd_backp(&lst, ft_lstnewp(split[i], ft_strlen(split[i])));
		i++;
	}
	free_split_p(split);
	// print_list(&lst);
	return (lst);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t	s;
	size_t	e;
	size_t	i;
	char	*tab;

	if (!s1 || !set)
		return (0);
	s = 0;
	e = ft_strlen(s1);
	i = 0;
	while (is_sep(s1[s], set) && s1[s])
		s++;
	while (e > s && is_sep(s1[e - 1], set))
		e--;
	tab = (char *)malloc(sizeof(char) * (e - s + 1));
	if (!tab)
		return (NULL);
	while (s < e)
	{
		tab[i++] = s1[s++];
	}
	tab[i] = 0;
	free(s1);
	return (tab);
}

t_listp	*split_redirection(t_listp **lst)
{
	t_listp	*tmp;
	int		flag;

	flag = 0;
	tmp = *lst;
	while (tmp)
	{
		tmp->content = ft_strtrim(tmp->content, " ");
		tmp->content2 = split_redirect(tmp->content, "<> ");
		tmp->content2 = realoc_split2(tmp->content2);
		tmp->content2 = realoc_split(tmp->content2);
		if (flag == 0)
			flag = check_redirection_end(tmp->content2);
		tmp = tmp->next;
	}
	if (flag == 1)
	{
		ft_lstclearp(*lst);
		return (NULL);
	}
	// print_command(lst);
	return (*lst);
}

t_listp	*lexer2(char *readline, t_listp *lst)
{
	lst = split_pipe(readline);
	if (lst != NULL)
		lst = split_redirection(&lst);
	return (lst);
}
