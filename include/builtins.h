/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:25:19 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/20 18:42:09 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <limits.h>
# include <linux/limits.h>

int		is_buildin(char *cmd);
void	exec_buildin(char **cmd, int mod);
void	cd(char	*path, char **cmd);
void	env(char **envp);
void	echo(char **cmd);
int		pwd(void);
void	export(char *str, t_dict *dict);
void	unset(char *var, t_dict *dict);
void	exec_exit(char **cmd);




void	ft_dictadd_back(t_dict **lst, t_dict *new);
t_dict	*ft_dictnew(char *content, char *key);
void	print_dict(t_dict **lst);
int		ft_dictsize(t_dict *lst);
void	ft_dictclear(t_dict	*lst);
char	**build_env(t_dict *dict);
t_dict	*get_dict(char **envp);

t_dict	*add_dict(t_dict *dict, char *key, char *content);
void	export_without_arg(t_dict *dict);

char	*get_key(char *str);
char	*get_content(char *str);

#endif