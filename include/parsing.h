/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:31:19 by ennollet          #+#    #+#             */
/*   Updated: 2023/06/14 11:07:57 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_listp
{
	char			*content;
	char			**content2;
	struct s_listp	*next;
}	t_listp;

typedef struct s_dict
{
	char			*key;
	char			*content;
	struct s_dict	*next;
}	t_dict;

void	print_list(t_listp **lst);
void	print_command(t_listp **lst);

int		is_token(char c);
char	*ft_strchr(char *s, int c);
t_listp	*lexer(char *line);
t_listp	*lexer2(char *readline, t_listp *lst);

t_listp	*expansion(t_listp **token, char **envp);

int		ft_strlen(char *str);
int		ft_strslen(char **str);

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin_char(char *str, char c);
char	*ft_strjoin(char *s1, char *s2);

t_listp	*substitution(t_listp **token, char **envp);

t_listp	*remove_quote(t_listp **token);

void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strndup(char *s, size_t size);

t_listp	*init_list(t_listp *list);
t_listp	*ft_lstnewp(char *content, int len);
int		is_empty(t_listp *list);
void	add_tailp(t_listp *list, t_listp *new);
void	ft_lstclearp(t_listp *lst);
void	ft_lstadd_backp(t_listp **lst, t_listp *new);
int		ft_lstsizep(t_listp *lst);

int		is_token(char c);
int		is_redirection(char c);

char	**ft_split(char const *s, char c);
int		test_flag(int flag, char content);

char	**ft_split_quote(char const *s, char *sep);
int		is_sep(char c, char *sep);
void	*ft_free_all(char **strs, int i);
void	*free_split_p(char **strs);

int		start_pipe(char *str);
int		test_multi(char *str);
char	check_triple(char *s);
int		end_pipe(char *str);

char	**split_redirect(char *s, char *sep);
char	**realoc_split(char **s);
char	**realoc_split2(char **s);
int		check_redirection_end(char **split);

char	*ft_strjoin_char(char *str, char c);
char	*ft_strjoin(char *s1, char *s2);
int		is_alpha(char c);
int		is_valid_variable(char c);
char	*check_variable(char *str, char **envp);
int		need_expand(char *str);
char	*expand_with_cote(char *str, char c);

char	**ft_split(char const *s, char c);
int		ft_strcmp(char *s1, char *s2);
char	**get_path_line(char **envp);
char	*ft_strjoin2(char *s1, char *s2);
void	*free_split_s(char **split, int i);

char	*check_file_exist(char *command);
char	*command_sub(char *str, char **envp);

void	ft_dictadd_back(t_dict **lst, t_dict *new);
t_dict	*ft_dictnew(char *content, char *key);
void	print_dict(t_dict **lst);
int		ft_dictsize(t_dict *lst);
void	ft_dictclear(t_dict	*lst);


t_listp	*parsing_aux(t_listp *bob, char *tmp, char **envp);
t_listp	*parsing(char *tmp, char **envp);

t_dict	*ft_unset(char *var, t_dict *dict);
t_dict	*ft_export(t_dict *dict, char *key, char *content);
void	export_without_arg(t_dict *dict);




#endif