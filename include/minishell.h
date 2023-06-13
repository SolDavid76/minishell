/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:22:40 by djanusz           #+#    #+#             */
/*   Updated: 2023/06/13 10:22:40 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "parsing.h"
# include "exec.h"

typedef struct s_shell
{
	t_dict	*dict;
	char	**envp;
	char	***cmds;
}			t_shell;

/* main.c */
void	ft_main_exit(int code);
t_shell	*get_shell(void);
char	**ft_envdup(char **envp);
char	***big_join(t_listp *lst);

/* utils.c */
int		ft_strlen(char *str);
int		ft_tablen(char **tab);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);



#endif